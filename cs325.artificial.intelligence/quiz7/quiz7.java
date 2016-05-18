package document;


public class quiz7 {

	public Term[] toBagOfWords(List<String> document, boolean df)
	{
		String PreviousTerm = "null";
		ObjectIntHashMap<String> map = new ObjectIntHashMap<>();
		Term[] terms = new Term[map.size()];
		int id, i = 0;
		
		for (String term : document) map.add(term);// unigram 
		
		for (String term : document) {
					map.add(PreviousTerm+term);  // create a bigram - add to map
					PreviousTerm = term;
		}
		
		for (ObjectIntPair<String> term : map)
			{
				id = getID(term.o);
				
				if (id < 0)	// term doesn't exist
					{
						id = id_count;
						term_id_map.put(term.o, ++id_count);
						term_list.add(new ObjectIntPair<String>(term.o, 0))						
					}
				
				terms[i++] = new Term(id, term.i);
				
				if (df) 
					term_list.get(id).i++;
			}
					
					Arrays.sort(terms);
					return terms;
		}
}
