public class WhatsPrinted08{
    public static void func(Derp d){
	d.x++;
	d = new Derp(222);
	
    }

    public static void main(String args[]){
	Derp d1 = new Derp(10);
	func(d1);
	System.out.println(d1);
    }
}
