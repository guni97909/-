import java.util.Scanner;

public class Check {
	public static void main(String[] args) {
		 Scanner scanner = new Scanner(System.in);
		 System.out.println(" ют╥б:");
		 String str = scanner.nextLine();
		

		String[][] st = new String[str.length() / 4 + 1][4];
		int z = 0;
		int x = 0;
		int y = 0;

		for (int i = 0; i < str.length() / 4 + 1; i++) {

			System.out.println();

			for (int j = 0; j < 4; j++) {
				if (i + j + z < str.length()) {
					st[i][j] = str.substring(i + j + z, i + j + 1 + z);
					System.out.print(st[i][j]);
				} else {
					st[i][j] = ("0");
					System.out.print(st[i][j]);
				}
				j = j++;
			}

			i = i++;
			z = z + 3;
		}

		System.out.println();
		System.out.println("__________________________");

		for (int i = 0; i < str.length() / 4 + 1; i++) {

			System.out.println();

			for (int j = 0; j < 4; j++) {
				if (i + j + y < str.length()) {
					st[i][j] = str.substring(i + j + y, i + j + 1 + y);
					System.out.print(stringToHex(st[i][j]));

				} else {
					st[i][j] = ("00");
					System.out.print((st[i][j])+" ");
				}
				j = j++;
			}

			i = i++;
			y = y + 3;
		}		
		System.out.println("");
		
		int[] sum = new int[st.length];
		int total = 0;
		for (int i = 0; i < st.length; i++) {
			String temp = "";
			for (int j = 0; j < st[i].length; j++) {
				if (!st[i][j].trim().equals("00")) {
					temp += stringToHex(st[i][j]);
					
				} else {
					temp += "00";
				}
			}
			temp = temp.replace(" ", "");
			sum[i] = Integer.parseInt(temp, 16);
			total += Integer.parseInt(String.valueOf(sum[i]), 10);
			
		}
		System.out.println(String.format("%X", total));
		System.out.println("");
		System.out.println("___________________________");
		
		System.out.print(String.format("%X", total));
		System.out.print("+ 1(carry) =");
		System.out.print(String.format("%X", total+1));
		
		System.out.println("");
		System.out.println("___________________________");
		
		System.out.print("~("+String.format("%X", total+1)+") =");
		System.out.print(String.format("%X", ~(total+1)));
		
		System.out.println("");
		System.out.println("___________________________");
		
		for (int i = 0; i < str.length() / 4 + 1; i++) {

			System.out.println();

			for (int j = 0; j < 4; j++) {
				if (i + j + x < str.length()) {
					st[i][j] = str.substring(i + j + x, i + j + 1 + x);
					System.out.print(stringToHex(st[i][j]));

				} else {
					st[i][j] = ("00");
					System.out.print((st[i][j])+" ");
				}
				j = j++;
			}

			i = i++;
			x = x + 3;
		}		
		System.out.println("");
		System.out.print(String.format("%X", ~(total+1)));
		System.out.println("");
		System.out.println(String.format("%X",total+~(total)));
		
		
		 scanner.close();
	}

	private static String stringToHex(String str1) {
		String result = "";
		for (int i = 0; i < str1.length(); i++) {
			result += String.format("%X ", (int) str1.charAt(i));
		}
		return result;
	}
	
}
