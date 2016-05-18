package trie.autocomplete;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import trie.Trie;
import trie.TrieNode;

public class HerreraAutocomplete extends Trie<List<String>> implements IAutocomplete<List<String>>  {
	
Map<String,Double> counter = new HashMap<String, Double>();	

Map<String,List<String>> recentPrefixes = new HashMap<String,List<String>>();

ArrayDeque <TrieNode<List<String>>> myDeq = new ArrayDeque<TrieNode<List<String>>>();


	@Override
	public List<String> getCandidates(String prefix) {
		
		List<String> list = new ArrayList<>(); //this list will be filled with candidates 
		
		TrieNode<List<String>> foundNode = find(prefix); // check if node exists and return that node if it does
		
		
		list = getWordsDownstream(foundNode, list, prefix);
		
			
		myDeq.clear();	
		return list;
		
		
	}
	
	public String getWordupstream (TrieNode<List<String>> Node , String Ret)
	{	
		//System.out.println("made it");
		if (Node.getParent() != null)
			{
			Ret = getWordupstream(Node.getParent(), Ret) + Node.getKey();
			return Ret;
			}
			
		return Ret;
		
	}
	public List<String> getWordsDownstream (TrieNode<List<String>> Node , List<String> list, String prefix)
	{
		
		if (recentPrefixes.containsKey(prefix))//populate with recent history
			{
				List<String> addtolist = recentPrefixes.get(prefix);
				
				for (int i =addtolist.size()-1 ; i > -1; i--)
				{	  
						
						list.add(addtolist.get(i));
				}
			}
			
		 return list = getWordsDownstream(Node, list);
	}
	
	
	public List<String> getWordsDownstream (TrieNode<List<String>> Node , List<String> list)
	{	
		Map<Character, TrieNode<List<String>>> childmap;
		
		
			if(Node.isEndState())
				if (list.size() < 20)
						
					list.add(getWordupstream(Node, "")); //add word to list
				else
					{
					return list;
					}
			if (Node.hasChildren())
			{
				
			childmap = Node.getChildrenMap(); // check if this node has children
			
			
			Set<Character> setlist = childmap.keySet(); // returns the set of character that are children
			
	
			
				for (char i : setlist) //add each child to the deque
				{	myDeq.add(Node.getChild(i));
				
				}
				
				if (myDeq!=null) // continue breadth first search
				getWordsDownstream(myDeq.removeFirst(), list);

			}
			else if (myDeq!=null) // if no children; continue poppin
			getWordsDownstream(myDeq.removeFirst(), list);
			 
				
			return list;
			
		
	}
	
	@Override
	public void pickCandidate(String prefix, String candidate) {
		
		
		List<String> list = new ArrayList<>();
		
		
		
		if (recentPrefixes.containsKey(prefix)) // check if prefix has been seen before
		{
			//System.out.println("      map contains prefix");
			if (counter.containsKey(candidate)) // check if we've seen candidate before
			{ 
				//System.out.println("     map contains candidate");
				Double addone = counter.get(candidate);
				counter.put(candidate,addone+1.00);
				
			}
			else
			{
				//System.out.println("   but map didnt contain candidate");
				counter.put(candidate, 1.00);
				
				list = recentPrefixes.get(prefix); // add the new candidate
				list.add(candidate);
				recentPrefixes.put(prefix, list);// update the map with new candidate
				
			}
		}
		if (!recentPrefixes.containsKey(prefix)) 
		{
			list.add(candidate);
			counter.put(candidate, 1.00); //create default list and count
		
			recentPrefixes.put(prefix, list); // add the new prefix with the candidate
		
		}
		
		
	}

}
