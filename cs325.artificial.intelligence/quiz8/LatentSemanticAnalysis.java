package semantics;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import org.la4j.Matrix;
import org.la4j.Vector;
import org.la4j.decomposition.SingularValueDecompositor;
import org.la4j.matrix.dense.Basic2DMatrix;

import utils.IntDoublePair;
import document.Term;
import document.VectorSpaceModel;
import edu.emory.clir.clearnlp.collection.pair.ObjectDoublePair;
import edu.emory.clir.clearnlp.component.utils.NLPUtils;
import edu.emory.clir.clearnlp.tokenization.AbstractTokenizer;
import edu.emory.clir.clearnlp.util.FileUtils;
import edu.emory.clir.clearnlp.util.lang.TLanguage;

/**
 * @author Jinho D. Choi ({@code jinho.choi@emory.edu})
 */
public class LatentSemanticAnalysis
{
	private VectorSpaceModel vs_model;
	private Matrix td_matrix;
	
	public LatentSemanticAnalysis(List<List<String>> documents, int k)
	{
		vs_model = new VectorSpaceModel();
		//List<Term[]> list = vs_model.toTFIDFs(documents);
		
		List<Term[]> list = new ArrayList<>();
		for (List<String> document : documents)
		list.add(vs_model.toBagOfWords(document, true));
				
		int T = vs_model.getTermSize(), D = list.size();
		td_matrix = new Basic2DMatrix(T, D);
		
		for (int docID=0; docID<D; docID++)
			for (Term term : list.get(docID))
				td_matrix.set(term.getID(), docID, term.getScore());
		
		////toLSA(k);
	}
	
	
	private void toLSA(int k)
	{
		SingularValueDecompositor d = new SingularValueDecompositor(td_matrix);
		Matrix[] usv = d.decompose();
		
		int[] top = getTopDiagonals(usv[1], k);		
		Matrix  u = new Basic2DMatrix(usv[0].rows(), k);
		Matrix  s = new Basic2DMatrix(k, k);
		Matrix  v = new Basic2DMatrix(usv[2].rows(), k);
		
		for (int i=0; i<k; i++)
		{
			u.setColumn(i, usv[0].getColumn(top[i]));
			s.setColumn(i, usv[1].getColumn(top[i]));
			v.setColumn(i, usv[2].getColumn(top[i]));
		}

		td_matrix = u.multiply(s).multiply(v.transpose());
	}
	
	private int[] getTopDiagonals(Matrix m, int k)
	{
		List<IntDoublePair> list = new ArrayList<>();
		
		for (int i=m.rows()-1; i>=0; i--)
			list.add(new IntDoublePair(i, m.get(i, i)));
		
		Collections.sort(list, Collections.reverseOrder());
		int[] indices = new int[k];
		
		for (int i=0; i<k; i++)
			indices[i] = list.get(i).getInt();
		
		return indices;
	}
	
	public List<ObjectDoublePair<String>> getTopSimilarTerms(String term, int k)
	{
					
		List<ObjectDoublePair<String>> list = new ArrayList<>();
		int termID= vs_model.getID(term);
		if(termID < 0) return list;
		
		for(int i = td_matrix.rows()-1; i>=0;i--)
		{
			if((i)!=termID)
				list.add(new ObjectDoublePair<String> ( vs_model.getTerm(i),
														getCosineSimilarityTerm(termID,i)));
		}
				
		Collections.sort(list, Collections.reverseOrder());
		return (k> list.size())? list : list.subList(0, k);
	}
	
	public double getCosineSimilarityTerm(int i, int j)
	{
		return getCosineSimilarity(td_matrix.getRow(i), td_matrix.getRow(j));
	}
	
	public double getCosineSimilarityDocument(int i, int j)
	{
		return getCosineSimilarity(td_matrix.getColumn(i), td_matrix.getColumn(j));
	}
	
	public double getCosineSimilarity(Vector v1, Vector v2)
	{
		return v1.innerProduct(v2) / Math.sqrt(v1.norm() * v2.norm());
	}
	
	static public void main(String[] args) throws Exception
	{
		final String inputDir = "C:/Users/Allen Herrera/Downloads/clustering/train";
		final String inputExt = ".txt";
		
		List<String> filenames = FileUtils.getFileList(inputDir, inputExt, true);
		AbstractTokenizer tokenizer = NLPUtils.getTokenizer(TLanguage.ENGLISH);
		List<List<String>> documents = new ArrayList<>();
		
		for (String filename : filenames)
			documents.add(tokenizer.tokenize(new FileInputStream(filename)));
		
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		LatentSemanticAnalysis lsa = new LatentSemanticAnalysis(documents, 1000);
		String line;
		int k = 5;
		
		while (true)
		{
			System.out.print("Enter a term: "); line = reader.readLine();
			
			for (ObjectDoublePair<String> p : lsa.getTopSimilarTerms(line.trim(), k))
				System.out.printf("%20s: %5.4f\n", p.o, p.d);
		}
	}
}