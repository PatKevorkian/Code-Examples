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

            for (int i = 0; i < Fds.Count && !found; i++)
            {
                tempStrDep = (string.Join("", Fds[i].left.ToArray()) + string.Join("", Fds[i].right.ToArray()));

                if (tempStrDep != schemaStr && containC(schemaStr, tempStrDep) && Fds[i].violation)
                {
                    found = true;
                    index = i;
                }
            }

            if (found)
            {
                //"crossing off" specific violation
                Fds[index].violation = false;
                //calculating bcnf on that level
                calc_bcnf(tempStrDep);
                //getting next decomposition n:       left(key)              +   entire schema - previous decomp
                tempStrDep = SortStringChars(string.Join("", Fds[index].left.ToArray()) + except(schemaStr, tempStrDep)); 
                //calculate bcnf on newly decompsed relation
                calc_bcnf(tempStrDep);

            }
            else
            {
                //already in bcnf
                bcnf.Add(schemaStr);
            }

        }
        //Reset function 
        public void reset()
        {
            if (Schema != null)
                Array.Clear(Schema, 0, Schema.Length);

            bcnf.Clear();
            Fds.Clear();
            closures.Clear();
            comboBox2.Items.Clear();
            comboBox3.Items.Clear();
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            listBox3.Items.Clear();
            label4.Text = "Schema (";
            schemaStr = "";
            comboBox2.Text = " ";
            comboBox3.Text = " ";
            comboBox1.Text = " ";
            button3.Enabled = true;
            comboBox2.Enabled = false;
            comboBox3.Enabled = false;
            button2.Enabled = false;
            button3.Enabled = false;

        }
        //function that calcualtes implicit FD's
        public void calc_impFD()
        {
            Fds.Clear();
            ell tempEllWoods;

            foreach (ell ellWoods in closures)
            {
                if (ellWoods.violation)
                {
                    foreach (String Ell_eanor in ellWoods.right)
                    {
                        if (!containC(string.Join("", ellWoods.left.ToArray()), Ell_eanor))
                        {
                            tempEllWoods = new ell();
                            tempEllWoods.right.Add(Ell_eanor);
                            tempEllWoods.left = ellWoods.left;
                            tempEllWoods.violation = true;
                            Fds.Add(tempEllWoods);

                        }
                    }
                }
            }

        }
        //function that returns true if contains in non consecutive order 
        public bool containC(String a, String b)
        {
            foreach (char subStr in b)
                if (!a.Contains(subStr))
                    return false;

            return true;
        }


        //function that returns a that not in b
        public String except(String a, String b)
        {
            String tempStr = "";

            foreach (char letter in a)
                if (!b.Contains(letter))
                    tempStr += letter;

            return tempStr;
        }

        //fnction that sorts a string 
        public static String SortStringChars(String s)
        {
            char[] c = s.ToCharArray();
            Array.Sort(c);
            return new String(c);
        }

        //function to compare left and right of closure and dependancy 
        public bool compare(ell close, ell func)
        {
            int count = 0;

            for (int i = 0; i < close.right.Count; i++)
            {
                for (int j = 0; j < func.left.Count; j++)
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
            for (int i = 0; i < closures.Count; i++)  //ell ellements in closures
            {
                //itterate over all dependencies  in Fds
                foreach (ell dependencies in Fds)
                {
                    //if comare is true add right side of dependencies to right side of elements
                    if (compare(closures[i], dependencies))
                    {
                        closures[i].right.AddRange(dependencies.right.Except(closures[i].right).ToList());
                        //sort left and right sides of closures 
                        closures[i].left.Sort();
                        closures[i].right.Sort();
                        //if the left side of closures is not equal to the right side set vilolation to true 
                        if (closures[i].left != closures[i].right)
                            closures[i].violation = true;

                        closures[i].right.Sort();
                    }

                }

            }


        }

        //global schema 
        String[] Schema;
        //a temp schema string 
        String schemaStr = "";
        //initialize new bcnf list 
        List<String> bcnf = new List<String>();
        //list of Functional dependencies 
        List<ell> Fds = new List<ell>(); 
        //list of closures 
        List<ell> closures = new List<ell>();
       
        //struct of left and right side of functional dep
        public class ell
        {
            public List<String> left;
            public List<String> right;
            public bool violation
            {
                get;
                set;
            }
            public ell()
            {
                left = new List<String>();
                right = new List<String>();
                violation = false;

            }

        }



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
            //on button click call reset function to reset program 
            reset();
        }


        private void button2_Click(object sender, EventArgs e)
        {
            //if combobox 2,3 are not empty 
            if (comboBox2.Text != " " && comboBox3.Text != " ")
            {
                //if there are items in list box 3 
                if(listBox3.Items.Count > 0 )
                {
                    //clear fds, closures, and list boxes. Enable buttion 3 
                    Fds.Clear();
                    closures.Clear();
                    button3.Enabled = true;
                    listBox2.Items.Clear();
                    listBox3.Items.Clear();
                }
                //adds functional dependencies to listbox 
                listBox1.Items.Add(comboBox2.SelectedItem + "->" + comboBox3.SelectedItem);
                //sorts fds in listbox 
                listBox1.Sorted = true;
                //clearing combo boxes 2 and 3 
                comboBox2.Text = " ";
                comboBox3.Text = " ";
            }

        }


        private void button3_Click(object sender, EventArgs e)
        {
            if (listBox3.Items.Count == 0 && comboBox2.Enabled)
            {
                String[] tempSplit;
                ell tempEll;
                Fds = new List<ell>();
                
                //adds fd's to fd list 
                foreach (string s in listBox1.Items)
                {
                    tempSplit = s.Split(("->").ToCharArray());
                    tempEll = new ell();

                    foreach (char k in tempSplit[0].ToCharArray())
                        tempEll.left.Add(k.ToString());

                    tempEll.violation = true;

                    foreach (char k in tempSplit[2].ToCharArray())
                        tempEll.right.Add(k.ToString());

                    Fds.Add(tempEll);
                }
                //if user adds extra dependancy after calculating bcnf
                if(closures.Count == 0)
                {
                    bcnf.Clear(); 
                     double count = Math.Pow(2, Schema.Length);
                     int ii, jj;
                     String temp = "";
                     closures = new List<ell>();
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

                        ell temp2 = new ell();


                        for (int p = 0; p < temp.Length; p++)
                        {
                            temp2.right.Add(temp[p].ToString());
                            temp2.left.Add(temp[p].ToString());
                        }
                        //adds closures to closure list 
                        closures.Add(temp2);
                        temp = "";
                    }
        
                }   
         
        
                //calculate the closures of the dependancies 
                calculate_closure();
                //clearing tempclosure 
                String tempClosure = "";

                //outputs closures in listbox in correct formant
                foreach (ell tempEllements in closures)
                {
                    tempClosure = "{";
                    foreach (String strEll in tempEllements.left)
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

                //calculating implicit FD's 
                calc_impFD();
                //calculating bcnf
                calc_bcnf(schemaStr);
                //add bcnf to lstbox 
                foreach (String bcnfStr in bcnf)
                    listBox3.Items.Add(bcnfStr);

            }
            // disable button (so no user error)
            else button3.Enabled = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (Schema != null)
                Array.Clear(Schema, 0, Schema.Length);

            bcnf.Clear();
            Fds.Clear();
            closures.Clear();
            comboBox2.Items.Clear();
            comboBox3.Items.Clear();
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            listBox3.Items.Clear();
            label4.Text = "Schema (";
            schemaStr = "";
            comboBox2.Text = " ";
            comboBox3.Text = " ";
            button3.Enabled = true;
            comboBox2.Enabled = false;
            comboBox3.Enabled = false;
            button2.Enabled = false;
            button3.Enabled = false;

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

            //enable combo boxes
            comboBox2.Enabled = true;
            comboBox3.Enabled = true;
            button2.Enabled = true;
            button3.Enabled = true;

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
                //adds combonations to combobox
                comboBox2.Items.Add(temp);
                comboBox3.Items.Add(temp);
                ell temp2 = new ell();


                for (int p = 0; p < temp.Length; p++)
                {
                    temp2.right.Add(temp[p].ToString());
                    temp2.left.Add(temp[p].ToString());
                }
                //adds closures to closure list 
                closures.Add(temp2);
                temp = "";
            }
            //sorting itmesin combobox 
            comboBox2.Sorted = true;
            comboBox3.Sorted = true;
        }


    }
}
