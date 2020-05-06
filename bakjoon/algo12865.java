package com.company;

import java.util.*;

public class algo12865 {
    public static void solv(){
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int K = sc.nextInt();
        long[]dp = new long[10000];
        List<int[]> l = new ArrayList<int[]>();
        for(int i=0; i<N; i++){
            int[] t = new int[2];
            t[0] = sc.nextInt();
            t[1] = sc.nextInt();
            l.add(t);
        }
        Collections.sort(l, new Comparator<int[]>() {
            @Override
            public int compare(int[] ints, int[] t1) {
                return ints[0]>t1[0]?1:-1;
            }
        });

    }
}
