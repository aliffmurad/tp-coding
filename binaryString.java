import java.util.*;
import java.io.*;
import java.text.*;

public class Bin2Str{
   	public static void main(String args[]) throws Exception
	{
		//declare FileReader
      		File bin = new File("binText.bin");

      		//declare FileWriter
      		PrintWriter output = new PrintWriter(new BufferedWriter(new FileWriter("textStr2.txt")));
	
		Scanner scanner = new Scanner(bin);
		String words = scanner.nextLine();

		String[] code = words.split(" ");
		String str = "";
		for(int i = 0; i < code.length; i++)
			str += (char)Integer.parseInt(code[i],2);
		
		System.out.println("Binary to String. Done.");
		String reverse = new StringBuffer(str).reverse().toString();
		
		output.println(reverse);
		System.out.println("String reversed. Done.");
		scanner.close();
		output.close();
	}
}
