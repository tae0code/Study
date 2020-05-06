package com.company;

import java.util.ArrayList;
import java.util.Scanner;

public class algo14501 {
    // loop()에서 접근이 가능하도록 static 선언
    static ArrayList<Integer> T = new ArrayList<Integer>();
    static ArrayList<Integer> P = new ArrayList<Integer>();
    static int N=0;
    public static void solv(){
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        for(int i=0; i<N; i++) {
            T.add(sc.nextInt());
            P.add(sc.nextInt());
        }
        System.out.println(loop(1, 0));
    }
    public static int loop(int D, int sum){
        /*
        loop(Day, sum)
        loop는 호출 될 때 해당 날짜에서 할 수 있는 경우의 수를 찾아 최대 값을 돌려준다.
         */
        if(D > N) return sum; // 퇴사일인 N일보다 더 일을 많이하는 경우는 없으니 sum이 최대값이다.
        if(T.get(D-1)+D > N+1){ // 현재 날짜에 들어온 업무 처리일이 퇴사일인 N일보다 크면 현재 날짜 + 1로 넘어간다.
            int s = loop(D+1, sum);
            return (s > sum) ? s : sum;
        }
        else{ // 만약 위의 경우가 아니라면, 현재 날짜에 들어온 업무를 처리할 수도, 안 할수도 있는 경우를 살펴본다.
            int s1 = loop(T.get(D-1)+D, sum+P.get(D-1));
            int s2 = loop(D+1, sum);
            return (s1 > s2) ? s1 : s2;
        }
    }
}
