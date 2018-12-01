package Homework2017.BridgeSegment.PKevorkian;

import simView.*;

import genDevs.modeling.*;
import DEVSJAVALab.vehicleEntity;
import GenCol.*;
import statistics.*;

public class BridgeSegment extends ViewableAtomic
{
	protected double green_time = 30;
	protected double yellow_time = 10;
	protected double red_time = 10;
	double carServingTime = 0;
	double remaining_Time;
    int Westcount = 0,Eastcount = 0;
    protected DEVSQueue Westq;
    protected DEVSQueue Eastq;
    entity car,WestcurrentCar,EastcurrentCar = null;
    
    public BridgeSegment() {this("BridgeSegment");}
    
    public BridgeSegment(String name){
        super(name);
        addInport("WestIn");
        addInport("EastIn");
        addOutport("WestOut");
        addOutport("EastOut");
        
        addTestInput("WestIn",new vehicleEntity("testCar", 10, 5, 1));

    }
    
    public void initialize(){
    	Westq = new DEVSQueue();
    	Eastq = new DEVSQueue();
        holdIn("Green_Empty", green_time);
        remaining_Time = green_time;
    }
    
    public void  deltext(double e,message x)
    {
    	Continue(e);
    	remaining_Time = remaining_Time -e;
    	
    	if(phaseIs("Green_Empty")){
    		for (int i=0; i< x.getLength();i++){
    			if (messageOnPort(x, "WestIn", i)) {
    				Westcount += 1;
    				car = x.getValOnPort("WestIn", i);
    				WestcurrentCar = car;
    				holdIn("Green_Occupied", ((vehicleEntity)WestcurrentCar).getProcessingTime());
    				}
    			else if (messageOnPort(x, "EastIn", i)) {
    				Eastcount += 1;
    				car = x.getValOnPort("EastIn", i);
    				EastcurrentCar = car;
    				holdIn("Green_Occupied", ((vehicleEntity)EastcurrentCar).getProcessingTime());
    				}
    			}
    		}
    	else { // phase is working_active, or break
    		for (int i=0; i< x.getLength();i++){
    			if (messageOnPort(x, "WestIn", i)) {
    				Westcount += 1;
    				car = x.getValOnPort("WestIn", i);
    				Westq.add(car);
    				}
    			}
    		for (int l=0; l< x.getLength();l++){
    			if (messageOnPort(x, "EastIn", l)) {
    				Eastcount += 1;
    				car = x.getValOnPort("EastIn", l);
    				Eastq.add(car);
    				}
    			}
    		}
    	}
    
    public void  deltint( ){
    	remaining_Time = remaining_Time - sigma;
    	if(phaseIs("Green_Occupied")){
    		if(remaining_Time>0){	// working time is not finished
    			if(!Westq.isEmpty()) {
    				WestcurrentCar = (entity)Westq.first();
    				holdIn("Green_Occupied", ((vehicleEntity)WestcurrentCar).getProcessingTime());
    				Westq.remove();
    				}
    			else if(!Eastq.isEmpty()){
    				EastcurrentCar = (entity)Eastq.first();
    				holdIn("Green_Occupied", ((vehicleEntity)WestcurrentCar).getProcessingTime());
    				Eastq.remove();
    				}
    			else
    				holdIn("Green_Empty", remaining_Time);
    		}
    		else if(remaining_Time == 0){
    			remaining_Time = yellow_time;
    			holdIn("Yellow", remaining_Time);
    		}
    	}
    	else if(phaseIs("Green_Empty")){ 
    		if(remaining_Time == 0){
    			remaining_Time = yellow_time;
    			holdIn("Yellow", remaining_Time);
    		}
    	}
    	else if(phaseIs("Yellow")){
    		remaining_Time = red_time;		
    		holdIn("Red", remaining_Time);
    	}
    	else if(phaseIs("Red")){
    		remaining_Time = green_time;
    		if(!Westq.isEmpty()) {
    			WestcurrentCar = (entity)Westq.first();
    			holdIn("Green_Occupied", ((vehicleEntity)WestcurrentCar).getProcessingTime());
    			Westq.remove();
    			}
    		else if(!Eastq.isEmpty()){
    			EastcurrentCar = (entity)Eastq.first();
    			holdIn("Green_Occupied", ((vehicleEntity)EastcurrentCar).getProcessingTime());
    			Eastq.remove();
    			}
    		else
    			holdIn("Green_Empty", remaining_Time);
    	}
    }
    
    public message out(){
    	message  m = new message();
    	if(phaseIs("Green_Occupied") && Westcount != 0){
    		Westcount = Westcount - 1;
    		content con = makeContent("WestOut", new vehicleEntity("car", 0, 0, 1));
    		m.add(con);
    		return m;
    		}
    	else if(phaseIs("Green_Occupied") && Eastcount != 0){
    		Eastcount = Eastcount - 1;
    		content con = makeContent("EastOut", new vehicleEntity("car", 0, 0, 1));
    		m.add(con);
    		return m;
    		}
    	else{
    		return new message();
    		}
    	}

}




