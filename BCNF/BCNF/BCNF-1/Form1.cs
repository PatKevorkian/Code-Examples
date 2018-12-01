using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BCNF_1
{

    public partial class Form1 : Form
    {   
        //calculates bcnf 
        public void calc_bcnf(String schemaStr)
        {
            bool found = false;
            String tempStrDep = "";
            int index = -1; 
            
            for(int i = 0; i < closures.Count && !found; i++)
            {
                tempStrDep = (string.Join("", closures[i].right.ToArray()));

                if (tempStrDep != schemaStr && containC(schemaStr,tempStrDep) && closures[i].violation)
                {
                    found = true;
                    index = i;
                } 
            }

            if (found)
            {
                //"crossing off" specific violation
                closures[index].violation = false;
                //Adding level of bcnf
                bcnf.Add(tempStrDep);
                //calculating bcnf on that level
                calc_bcnf(tempStrDep);
                //getting next decomposition n:       left(key)              +   entire schema - previous decomp
                tempStrDep = SortStringChars(string.Join("", closures[index].left.ToArray()) + except(schemaStr, tempStrDep));    //stupid problem 
                //add newly decomposed relation to bcnf list
                bcnf.Add(tempStrDep);
                //calculate bcnf on newly decompsed relation
                calc_bcnf(tempStrDep);

            }

        }


        //if contains in non consecutive order 
        public bool containC(String a, String b)
        {
            foreach (char subStr in b)
                if (!a.Contains(subStr))
                    return false;

            return true;
        }


        //returns a that not in b
        public String except(String a, String b)
        {
            String tempStr = "";

            foreach (char letter in a)
                if (!b.Contains(letter))
                    tempStr += letter;

            return tempStr;
        }
        //sorts a string 
        public static String SortStringChars(String s)
        {
            char[] c = s.ToCharArray();
            Array.Sort(c);
            return new String(c);
        }

        //compares left and right of closure and dependancy 
        public bool compare(ell close, ell func)
        {
            int count = 0; 
            
            for(int i = 0 ; i < close.right.Count; i++)
            {
                for(int j = 0; j < func.left.Count; j++)
                {
                    if (close.right[i] == func.left[j])
                        count++;
                }
            }
            return count == func.left.Count;
        }

        //function to calculate closures 
        public void calculate_closure()
        {
            //itterate over all ellements in closures 
            for(int i = 0; i < closures.Count; i++)  //ell ellements in closures
            {
                //itterate over all dependencies  in Fds
                foreach (ell dependencies in Fds)
                {
                    //if comare is true add right side of dependencies to right side of elements
                    if (compare(closures[i], dependencies))
                    {
                        closures[i].right.AddRange(dependencies.right.Except(closures[i].right).ToList());
                        closures[i].left.Sort();
                        closures[i].right.Sort();
                        if (closures[i].left != closures[i].right)
                        closures[i].violation = true;

                        closures[i].right.Sort(); 
                    }

                }

            }


        }
        //global schema 
        String[] Schema;
        String schemaStr = "";
        List<String> bcnf = new List<String>();
         

        //struct of left and right side of functional dep
        public class ell
        {
            public List<String> left;
            public List<String> right;
            public bool violation
            {
                get; set;
            }

           public ell()
            {
                left = new List<String>();
                right = new List<String>();
                violation = false; 
                    
            }

        }

        //list of Functional dependencies 
        List<ell> Fds, closures;

        public Form1()
        {
            //Adds 1-27 to the combo box for schema size
            InitializeComponent();
            for (int i = 1; i < 27; i++)
            {
                comboBox1.Items.Add(i);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //changes the numbers in size of schema to letters, then output in schema label
            int i = 0;
            Schema = new String[int.Parse(comboBox1.Text)];
            for (char letter = 'A'; letter < Convert.ToChar('A' + int.Parse(comboBox1.Text)); letter++)
            {
                Schema[i++] = letter.ToString();
                label4.Text += Schema[i - 1] + ",";
                schemaStr += Schema[i - 1];
            }
            label4.Text = label4.Text.Remove(label4.Text.Length - 1);
            label4.Text += ")";



            //calculates every combonation of the letters in schema (used for combo box and for closures)
            double count = Math.Pow(2, Schema.Length);
            int ii, jj;
            String temp = "";
            closures = new List<ell>();
            //String value;
            for (ii = 1; ii <= count - 1; ii++)
            {
                String str = Convert.ToString(ii, 2).PadLeft(Schema.Length, '0');
                for (jj = 0; jj < str.Length; jj++)
                {
                    if (str[jj] == '1')
                    {
                        temp += Schema[jj];
                    }
                }
                
                comboBox2.Items.Add(temp);
                comboBox3.Items.Add(temp);
                ell temp2 = new ell();
                //temp2.left = new List<string>();
               // temp2.right = new List<string>();
               

                for (int p = 0; p < temp.Length; p++)
                {
                    temp2.right.Add(temp[p].ToString());
                    temp2.left.Add(temp[p].ToString());
                }

               // temp2.violation = false;
                closures.Add(temp2);
                temp = "";
            }

            comboBox2.Sorted = true;
            comboBox3.Sorted = true;
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            //adds functional dependencies to listbox 
            listBox1.Items.Add(comboBox2.SelectedItem + "->" + comboBox3.SelectedItem);
            listBox1.Sorted = true;
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            String[] tempSplit;
            ell tempEll;
            Fds = new List<ell>();
          
            foreach (string s in listBox1.Items)
            {
                tempSplit = s.Split(("->").ToCharArray());
                tempEll = new ell();
                //tempEll.left = new List<string>();
                //tempEll.right = new List<string>();

                foreach (char k in tempSplit[0].ToCharArray())
                tempEll.left.Add(k.ToString());

                foreach (char k in tempSplit[2].ToCharArray())
                    tempEll.right.Add(k.ToString());

                Fds.Add(tempEll);
            }
            calculate_closure();

            String tempClosure = "";

            //outputs closures in listbox in correct formant
            foreach(ell tempEllements in closures)
            {
                tempClosure = "{";
                foreach(String strEll in tempEllements.left)
                {
                    tempClosure += strEll + ",";
                }
                tempClosure = tempClosure.Remove(tempClosure.Length - 1);
                tempClosure += "}+ = {";
                foreach (String strEll in tempEllements.right)
                {
                    tempClosure += strEll + ",";
                }
                tempClosure = tempClosure.Remove(tempClosure.Length - 1);
                tempClosure += "}";
                listBox2.Items.Add(tempClosure);
            }

            calc_bcnf(schemaStr);

            foreach(String bcnfStr in bcnf)
            listBox3.Items.Add(bcnfStr);
        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void listBox3_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void listBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
