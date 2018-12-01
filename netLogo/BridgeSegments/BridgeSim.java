package Homework2017.BridgeSegment.PKevorkian;

import simView.*;

import DEVSJAVALab.vehicleEntity;
import GenCol.*;
import statistics.*;
import genDevs.plots.*;
import java.awt.*;
import java.lang.*;
import genDevs.modeling.*;
import genDevs.simulation.*;
import pulseExpFrames.pulseGenr;
import GenCol.*;
import java.util.*;

public class BridgeSim extends  ViewableDigraph{
	public BridgeSim(){
		super("BridgeSim");
	
	ViewableAtomic EastCarGen = new carGenr("EastCarGen",3);
	add(EastCarGen);
	
	ViewableAtomic WestCarGen = new carGenr("WestCarGen",6);
	add(WestCarGen);
	
	ViewableAtomic EastBridge = new BridgeSegment("EastBridge");
	add(EastBridge);
	
	ViewableAtomic MiddleBridge = new BridgeSegment("MiddleBridge");
	add(MiddleBridge);
	
	ViewableAtomic WestBridge = new BridgeSegment("WestBridge");
	add(WestBridge);
	
	addCoupling(EastCarGen,"out",EastBridge,"EastIn");
	addCoupling(WestCarGen,"out",WestBridge,"WestIn");
	addCoupling(EastBridge,"EastOut",MiddleBridge,"EastIn");
	addCoupling(MiddleBridge,"EastOut",WestBridge,"EastIn");
	addCoupling(WestBridge,"WestOut",MiddleBridge,"WestIn");
	addCoupling(MiddleBridge,"WestOut",EastBridge,"WestIn");

	addCoupling(EastBridge,"WestOut",this,"out");
	addCoupling(WestBridge,"EastOut",this,"out");

	}
	
	public void layoutForSimView()
    {
        preferredSize = new Dimension(721, 379);
        if((ViewableComponent)withName("EastCarGen")!=null)
             ((ViewableComponent)withName("EastCarGen")).setPreferredLocation(new Point(352, 66));
        if((ViewableComponent)withName("WestCarGen")!=null)
             ((ViewableComponent)withName("WestCarGen")).setPreferredLocation(new Point(184, 59));
        if((ViewableComponent)withName("EastBridge")!=null)
             ((ViewableComponent)withName("EastBridge")).setPreferredLocation(new Point(-28, 150));
        if((ViewableComponent)withName("MiddleBridge")!=null)
             ((ViewableComponent)withName("MiddleBridge")).setPreferredLocation(new Point(475, 170));
        if((ViewableComponent)withName("WestBridge")!=null)
             ((ViewableComponent)withName("WestBridge")).setPreferredLocation(new Point(276, 248));
    }
}
