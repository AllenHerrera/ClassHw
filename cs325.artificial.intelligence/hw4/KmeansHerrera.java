package document;

import edu.emory.clir.clearnlp.util.MathUtils;

public class KmeansHerrera extends AbstractKmeans{

	@Override
	protected double distance(Term[] document, double[] centroid)
	{
		double num = 0, a = 0, b;
		
		for (Term term : document)
		{
			a += MathUtils.sq(term.getScore());
			num += term.getScore() * centroid[term.getID()];
		}

		a = Math.sqrt(a);
		b = Math.sqrt(MathUtils.sumOfSquares(centroid));
		return -num / (a * b);
	}
}


