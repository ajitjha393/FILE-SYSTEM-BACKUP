public class PEP {
	public PEP(int[] process, int[] bt, int[] at, int[] pt) {
		int n = process.length;
		int i = 0, j = 0;
		int temp, time = 0, av;

		int tt[] = new int[n];
		int wt[] = new int[n];
		int b[] = new int[n];
		int a[] = new int[n];
		int[] st = new int[n];
		int[] rt = new int[n];
		
		for (i = 0; i <= n - 2; ++i) {
			for (j = i; j <= n - 1; ++j) {
				if (at[i] > at[j]) {
					temp = at[i];
					at[i] = at[j];
					at[j] = temp;
					temp = bt[i];
					bt[i] = bt[j];
					bt[j] = temp;
					temp = pt[i];
					pt[i] = pt[j];
					pt[j] = temp;
					temp = process[i];
					process[i] = process[j];
					process[j] = temp;
				}
			}
		}
		

		for (i = 0; i < n; ++i) {
			b[i] = bt[i];
			a[i] = at[i];
		}
		
		do {
			av = 0;
			for (i = 0; i < n; ++i)
				if (at[i] <= time)
					++av;
			int hp;
			int max = 0;
			if (bt[0] == 0) {
				for (i = 1; i < n; ++i)
					if (bt[i] != 0) {
						max = i;
						break;
					}
			}
			for (i = 0; i < av; ++i) {
				if ((pt[max] > pt[i]) && bt[i] > 0)
					max = i;
			}
			hp = max;
			bt[hp] -= 1;
			++time;
			if (bt[hp] == 0)
				tt[hp] = time;
		} while (sum(bt, n) != 1);
		double att = 0, awt = 0, art = 0;
		double s1 = 0, s2 = 0, s3 = 0;
		for (i = 0; i < n; ++i) {
			tt[i] = tt[i] - at[i];
			wt[i] = tt[i] - b[i];
			st[i] = wt[i] + a[i];
			rt[i] = st[i] - a[i];
		}

		System.out.println();
		for (int h = 0; h < n; ++h)
			System.out.println("Turn around time of process " + (h + 1) + " = " + tt[h] + "  wait time = " + (wt[h])
					+ " response time" + rt[h]);

		for (i = 0; i < n; ++i) {
			s1 += tt[i];
			s2 += wt[i];
			s3 += rt[i];
		}
		att = s1 / n;
		awt = s2 / n;
		art = s3 / n;
		System.out.println("Average Turn around time= " + att);
		System.out.println(" Average wait time= " + awt);
		System.out.println(" Average response time= " + art);
	}
	
	int sum(int bt[], int n) {
		int s = 0;
		for (int i = 0; i < n; ++i)
			s += bt[i];
		if (s == 0)
			return 1;
		else
			return 0;
	}
}