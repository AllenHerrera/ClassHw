package hw3;

import java.io.*;
import java.util.HashMap;

public class Bayes {

	
	public static void main(String[] args) throws FileNotFoundException, IOException {
		HashMap<String, SingleNode> classes = new HashMap<String, SingleNode>();
		
		//Train method
			//read in text file by line
			//first column is class, check if its in the array
				// if not in array add it
				// else/then update the counts of all the attributes seen given that class that is seen
		
		int totalClassCount =0;
		//try (BufferedReader br = new BufferedReader(new FileReader("src/mushroom.training.txt"))) {
		try (BufferedReader br = new BufferedReader(new FileReader(args[0]))) {
		    String line;
		  
		   
		    while ((line = br.readLine()) != null) {
		       int column = 0;
		       String currentClass = null;
		       for( String attribute : line.split("\t")){
		    	   
		    	   if(column == 0) {
		    		   totalClassCount++;
			    	   if(classes.containsKey(attribute)){
			    		   //class exists just update count
			    		   classes.get(attribute).count++;
			    		   
			    	   } else {
			    		   //create new class
			    		   classes.put(attribute, new SingleNode(attribute,1));
			    	   }
			    	   currentClass=attribute;
			    	   
			    	 
		    	   } else {
		    		   //not the class attribute, class should exist
		    		  
		    		   classes.get(currentClass).updateCount((column+attribute));
		    		   
		    	   }
		    	   column++;
		    	  
		       }
		     
		    }
		}
		
		//Test method
			//read in line
			//start with first class in the hashmap, calculate the prob that it is that class, save it some variable
			// iterate through hashmap and report the highest likely class this transaction should be
				// compare that with the actual classification and determine if we classified it correctly or not
			//continue looping through transactions doing the above
			//report how many total correct of how many we tried classifying 
		
		//PrintWriter writer = new PrintWriter("src/Testing.txt", "UTF-8");
		PrintWriter writer = new PrintWriter(args[2], "UTF-8");
		writer.println("My Classification: Tuple");
		
		int correct =0;
		int totalTested =0;
		//try (BufferedReader br = new BufferedReader(new FileReader("src/mushroom.test.txt"))) {
		try (BufferedReader br = new BufferedReader(new FileReader(args[1]))) {
		    String line;
		   // int count =0;
		    HashMap<String, Double> cTOP = new HashMap<String, Double>();
		 //   for(String klass: classes.keySet() ){
		//    	cTOP.put(klass, 1.0); 
		   // }
		    while ((line = br.readLine()) != null) {
		       int column = 0;
		       double highestChance= 0.0;
		       String likelyClass = null;
		       String answer = null;
		       //set to probability of the class itself
		       for(String klass: classes.keySet() ){
			    	cTOP.put(klass, classes.get(klass).getProbability(totalClassCount)); 
			    }
		       //iterate through elements
		       for( String attribute : line.split("\t")){
		   
		    	   if(column != 0) {
			    	 for(String klass: classes.keySet() ){
			    		 
			    		// System.out.printf("%.10f",classes.get(klass).getJointProbability(column+attribute));
			    		 cTOP.put(klass, cTOP.get(klass)*classes.get(klass).getJointProbability((column+attribute)));
			    		 
			    	 }
		    	   } else {
		    		   //save the class to compare with our result
		    		   
		    		   answer = attribute;
		    	   }
		    	   column++;
		    	  
		       }
		       //find highest and compare to answer
		       for(String klass: classes.keySet() ){
		    	  // System.out.println(cTOP.get(klass));
			    	if(cTOP.get(klass)>highestChance){
			    		
			    		highestChance = cTOP.get(klass);
			    		likelyClass = klass;
			    	} 
			    }
		       writer.println(likelyClass+ ": "+line);
		       //System.out.println("answer " + answer + " likelyClass:  "+ likelyClass);
		       if(answer.equals(likelyClass)){
		    	   correct++;
		       }
		       totalTested++;
		    }
		}
		writer.println(correct + " correct out of "+ totalTested);
		writer.println((double)correct/totalTested);
		System.out.println(correct + " correct out of "+ totalTested);
		System.out.println((double)correct/totalTested);
		writer.close();
	}

}
