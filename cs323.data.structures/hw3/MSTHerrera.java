package graph.span;

import graph.Edge;
import graph.Graph;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Set;

public class MSTHerrera implements MSTAll {

	@Override
	public List<SpanningTree> getMinimumSpanningTrees(Graph graph) {
		
		PriorityQueue<Edge> Queue = new PriorityQueue<Edge>();
		SpanningTree Tree = new SpanningTree();
		List<SpanningTree> TreeSet = new ArrayList<SpanningTree>();
		Set<Integer> set = new HashSet<Integer>();
		
		add(Queue,set,graph,0);
		
		FindSpanningTree(TreeSet, Queue, Tree, set, graph);
		
		return TreeSet;
	}
	public void FindSpanningTree(List<SpanningTree> TreeSet, PriorityQueue<Edge> Queue, SpanningTree Tree, Set<Integer> set, Graph graph)
	{
		
		if (Tree.size()+1 == graph.size())
		{
			TreeSet.add(Tree);
			System.out.println(Tree);
     		System.out.println(Tree.getTotalWeight());
			return;
			
		}
		
		if (RemoveDuplicates(Queue, set)) return;
		
		Edge edge;
		PriorityQueue<Edge> NewQueue;
		SpanningTree NewTree;
		Set<Integer> NewSet;
		
		do 
		{
			edge = Queue.poll();
			
			//System.out.println("polled edge: " + edge);
			//System.out.println("set: " + set);
			
			NewQueue= new PriorityQueue<Edge>(Queue);
			NewTree = new SpanningTree(Tree);
		    NewSet = new HashSet<Integer>(set);
		  
		   // System.out.println("NewSet: " + NewSet);
		    
		    NewTree.addEdge(edge);
		    add(NewQueue, NewSet, graph, edge.getSource());
		    
		    FindSpanningTree(TreeSet,NewQueue,NewTree,NewSet,graph);
		    
		 // System.out.println("polled edge: " + edge);
		//	System.out.println("set: " + set);
		 // System.out.println("queuepeek: " + Queue.peek());
		
		}
		while(!Queue.isEmpty() && edge.compareTo(Queue.peek())==0);
		
	}
	
	private boolean RemoveDuplicates (PriorityQueue<Edge> Queue, Set<Integer> set)
	{
		//System.out.println("entering Duplicates");
		List<Edge> SharedEdges = new ArrayList<>();
		
		//System.out.println("queue: " + Queue);
		//System.out.println("set: " + set);
		
		for(Edge edge : Queue)
		{	
			//System.out.println("Checking: " + edge);
			
			if (set.contains(edge.getSource())){ 
				
			//	System.out.println("removing: " + edge);
				
				SharedEdges.add(edge);}
			
		}
		Queue.removeAll(SharedEdges);
		return Queue.isEmpty();
		
	}
	
	private void add(PriorityQueue<Edge> queue, Set<Integer> set, Graph graph, int target)
	{
		set.add(target);
		
		//System.out.println("target is: " + target);
		//System.out.println("incoming edges are: " + graph.getIncomingEdges(target));
		
		for (Edge edge : graph.getIncomingEdges(target))
		{
			//System.out.println("checking incoming edge: " + edge);
			///System.out.println("getSource: " + edge.getSource());
			//System.out.println("set: " + set);
			
			if (!set.contains(edge.getSource()))
				queue.add(edge);
		}
	}
	

	
}
