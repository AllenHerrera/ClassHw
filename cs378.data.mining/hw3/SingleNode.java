package hw3;

import java.util.HashMap;


public class SingleNode {

	public String name;
	public int count;
	//some conditional count where I can up the counter
	HashMap<String, Integer> JointCount = new HashMap<String, Integer>();

	 
	SingleNode(String name, int count) {
		this.name=name;
		this.count = count;
	}

	public void updateCount(String name) {
		if(JointCount.containsKey(name)){
			JointCount.put(name, JointCount.get(name) + 1);
		} else {
			JointCount.put(name,2); 
		}
	}
	public double getProbability(int totalCount) {
		return (double)this.count/totalCount;
		
	}
	public double getJointProbability(String name) {
		if(JointCount.containsKey(name)){
			//System.out.println(name+": " + JointCount.get(name));
			return (double) JointCount.get(name)/this.count;
		}
		//for the unseen case I added just 1
		
		return (double)1/this.count;
	}
}
