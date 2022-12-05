package protocol;

import java.util.Scanner;

public class protocol {
	public static void main(String[] args) {
		 Scanner scanner = new Scanner(System.in);
		 System.out.println(" 입력:");
		 String str = scanner.nextLine();
		 
		 String type=str.substring(24, 28);
		 
		 
	 
		 System.out.println("1. Ethernet");
		 System.out.print("  1) Destination Address : "+str.substring(0,2)+":"+str.substring(2,4)+":"
					 +str.substring(4,6)+":"+str.substring(6,8)+":"+str.substring(8,10)+":"+str.substring(10,12));
		 
		 if(Integer.parseInt(str.substring(0,2),16)%2==0) {
			 System.out.println(" / Unicast");
		 }else {
			 System.out.println("/ Broadcast");
		 }
		 
		 System.out.print("  2) Source Address : "+str.substring(12,14)+":"+str.substring(14,16)+":"
					 +str.substring(16,18)+":"+str.substring(18,20)+":"+str.substring(20,22)+":"+str.substring(22,24));
		 
		 if(Integer.parseInt(str.substring(12,14),16)%2==0) {
			 System.out.println(" / Unicast");
		 }else {
			 System.out.println("/ Broadcast");
		 }
		 
		 
		 
		switch(type) {
		case "0800":   //IP
			
			
			 System.out.println("  3) Type : "+type+" / IP");
			
			 
			 
			 int num=Integer.parseInt(str.substring(40,41));
			 
			 String bin = "";
				
				
			 bin = (num % 2) + bin;
			 
			 num /= 2;

			 bin = (num % 2) + bin;
			 
			 num /= 2;

			 bin = (num % 2) + bin;
			 
			 num /= 2;

			 bin = (num % 2) + bin;
			 
			 num /= 2;
			 
			 			 
			 
			 System.out.println("2. IP");
			 System.out.println("  1) Version :"+"0"+str.substring(28, 29));
			 System.out.print("  2) Header Length : "+str.substring(29, 30)+" / "+Integer.parseInt(str.substring(29, 30))*4+" byte : ");
			 if(Integer.parseInt(str.substring(29, 30))*4<=20) {
				 System.out.println("No option");
				 
			 }else {
				 System.out.println((Integer.parseInt(str.substring(29, 30))*4-20)+" option");
			 }
				 
			 System.out.println("  3) Service Type : "+str.substring(30, 32)+" No service type");
			 System.out.println("  4) Total Length : "+str.substring(32, 36)+" / "+Integer.parseInt(str.substring(32, 36),16)+" bytes : "
					               +(Integer.parseInt(str.substring(32, 36),16)-Integer.parseInt(str.substring(29, 30))*4)+"bytes payload");
			 System.out.println("  5) Identification : "+str.substring(36, 40)+" / "+Integer.parseInt(str.substring(36, 40),16));
			 
			 
			 System.out.println("  6) Flags : "+str.substring(40,41)+" / "+bin);
			 System.out.println("      - Reverse : "+ bin.substring(0,1));			 
			 System.out.print("      - Don’t Fragment : "+ bin.substring(1,2)+" / ");
			 if(Integer.parseInt(bin.substring(1,2))==1) {
				 System.out.println("Unable to fragment");
			 }else {
				 System.out.println("able to fragment");
			 }
			 System.out.print("      - More : "+ Integer.parseInt(bin.substring(2,4))+" / ");
			 if(Integer.parseInt(bin.substring(2,4))==1) {
				 System.out.println("Have more fragments");
			 }else {
				 System.out.println("No more fragments");
			 }
			 
			 
			 System.out.print("  7) Offset : "+str.substring(41,44)+" / ");
			 if(Integer.parseInt(str.substring(41,44))*8>=2500) {
				 System.out.println("Third Fragment");
			 }else if(Integer.parseInt(str.substring(41,44))*8>=1200) {
				 System.out.println("Second Fragment");
			 }else {
				 System.out.println("First fragments");
			 }
			 
			 System.out.println("  8) TTL : "+str.substring(44,46)+" / "+Integer.parseInt(str.substring(44, 46),16)+"hops");
			 System.out.println("  9) Protocol : "+Integer.parseInt(str.substring(46, 48)));
			 System.out.println("  10) Checksum : "+str.substring(48,52));
			 
			 System.out.println("  11) Source Address : "+str.substring(52,60)+" / "+ Integer.parseInt(str.substring(52, 54),16)+"."
				 + Integer.parseInt(str.substring(54, 56),16)+"."+ Integer.parseInt(str.substring(56, 58),16)+"." + Integer.parseInt(str.substring(58, 60),16));
			 
			 System.out.println("  12) Destination Address : "+str.substring(60,68)+" / "+ Integer.parseInt(str.substring(60, 62),16)+"."
					 + Integer.parseInt(str.substring(62, 64),16)+"."+ Integer.parseInt(str.substring(64, 66),16)+"." + Integer.parseInt(str.substring(66, 68),16));
			 
			 
			 
			 
			 
			 if(Integer.parseInt(str.substring(46, 48))==6) {  //TCP
				 
				 System.out.println("3. TCP");
				 
				 String bits=bytesToBinaryString((byte) Integer.parseInt(str.substring(93,96),16));
				
				 System.out.print("  1) Source Port : "+str.substring(68,72)+" / "+Integer.parseInt(str.substring(68, 72),16));
	             if(Integer.parseInt(str.substring(68, 72),16)<=1023) {
	                System.out.println("(Well-Known Port) : WWW");
	             }else if(Integer.parseInt(str.substring(68, 72),16)<=49151) {
	                System.out.println("Registered (User) Port Numbers");
	             }else {
	                System.out.println("Private/Dynamic Port Numbers");
	             }
	             
	             System.out.println("  2) Destination Port : "+str.substring(72,76)+" / "+Integer.parseInt(str.substring(72, 76),16)+" : Client Port");
	             System.out.println("  3) Sequence number : "+str.substring(76,84));
	             
	             System.out.println("  4) Ack number : "+str.substring(84,92));
	             
	             System.out.print("  5) Header Length : "+str.substring(92,93)+" / " +Integer.parseInt(str.substring(92,93))*4+" bytes :");
	             if(Integer.parseInt(str.substring(92, 93))*4<=20) {
	                System.out.println("No option");
	                
	             }else {
	                System.out.println(" option "+(Integer.parseInt(str.substring(92, 93))*4-20)+" bytes");
	             }
	             
	             
	             System.out.println("  6) Control Bits : "+Integer.parseInt(str.substring(93,96))+" / "+bits);
	             System.out.print("      - Urgent : "+Integer.parseInt(bits.substring(2, 3))+" / ");
	             if(Integer.parseInt(bits.substring(2, 3))==0) {
	                System.out.println("Not urgent");
	             }else {
	                System.out.println("urgent");
	             }
	             System.out.print("      - Ack : "+Integer.parseInt(bits.substring(3, 4))+" / ");
	             if(Integer.parseInt(bits.substring(3, 4))==0) {
	                System.out.println("Acknowlegment X");
	             }else {
	                System.out.println("Acknowlegment");
	             }
	             System.out.print("      - Push : "+Integer.parseInt(bits.substring(4, 5))+" / ");
	             if(Integer.parseInt(bits.substring(4, 5))==0) {
	                System.out.println("Normal");
	             }else {
	                System.out.println("Push");
	             }
	             System.out.print("      - Reset : "+Integer.parseInt(bits.substring(5, 6))+" / ");
	             if(Integer.parseInt(bits.substring(5, 6))==0) {
	                System.out.println("Normal");
	             }else {
	                System.out.println("Reset");
	             }
	             System.out.print("      - Syn : "+Integer.parseInt(bits.substring(6, 7))+" / ");
	             if(Integer.parseInt(bits.substring(6, 7))==1) {
	                if(Integer.parseInt(bits.substring(3, 4))==0) {
	                   System.out.println("Connect request");
	                }else {
	                   System.out.println("Connection setup");
	                }
	                
	             }else {
	                System.out.println("Connection setting");
	             }
	             System.out.print("      - Fin : "+Integer.parseInt(bits.substring(7, 8))+" / ");
	             if(Integer.parseInt(bits.substring(7, 8))==1) {
	                if(Integer.parseInt(bits.substring(3, 4))==0) {
	                   System.out.println("request for release");
	                }else {
	                   System.out.println("response for release");
	                }
	                
	             }else {
	                System.out.println("Not Connection Release");
	             }
	             
	             
	             System.out.println("  7) Window Size : "+str.substring(96, 100)+" / "+Integer.parseInt(str.substring(96, 100),16)+" bytes");
	             System.out.println("  8) Checksum : "+str.substring(100, 104));
	             
	             System.out.print("  9) Urgent Point : "+str.substring(104, 108)+" / ");
	             if(Integer.parseInt(bits.substring(2, 3))==0) {
	                System.out.println("Not urgent");
	             }else {
	                System.out.println("urgent");
	             }
	             
	             System.out.print("  10) Option : "+str.substring(108, str.length())+" / "+(str.length()-108)/2+" bytes");
			
        	 }
		     else if(Integer.parseInt(str.substring(46, 48))==1) {  //ICMP
				 System.out.println("3. ICMP");
				 System.out.println("  1) Type : "+str.substring(68,70));
				 System.out.println("  2) Code:  "+str.substring(70,72));
				 System.out.println("  3) Checksum:  "+str.substring(72,76));
				 System.out.println("  4) Identifier:  "+str.substring(76,80));
				 System.out.println("  5) Sequence number:   "+str.substring(80,84));
				 System.out.println("  6) Data section :   "+str.substring(84,str.length()));
				 
				 
				 
				 
		     }else if(Integer.parseInt(str.substring(46, 48))==17){
		    	 System.out.println("3. UDP");
		    	 System.out.println("  1) Source Port number : "+str.substring(68,72));
				 System.out.println("  2) Destination port number:  "+str.substring(72,76));
				 System.out.println("  3) Total length:  "+str.substring(76,80)+" / "+Integer.parseInt(str.substring(76, 80),16)+" bytes : "
						 +(Integer.parseInt(str.substring(76, 80),16)-20)+"bytes payload");
				 System.out.println("  4) Checksum:  "+str.substring(80,str.length()));
				 
		     }else {
				 System.out.println("High Protocol x");
		     }
			break;
		
			
			
			
		case "0806":  //ARP
			System.out.println("  3) Type : "+type+" / ARP");
			
			System.out.println("2. ARP");
			System.out.print("  1) H/W Type : "+str.substring(28, 32)+" / ");
			
			if(Integer.parseInt(str.substring(28, 32))==1) {
	            System.out.println("Ethernet");
	         }else if(Integer.parseInt(str.substring(28, 32))==2) {
	        	 System.out.println("Experimetal Ethernet");
	         }else if(Integer.parseInt(str.substring(28, 32))==3) {
	        	 System.out.println("Amteur Radio");
	         }else if(Integer.parseInt(str.substring(28, 32))==4) {
	        	 System.out.println("Proteon ProNET Token Ring");
	         }else if(Integer.parseInt(str.substring(28, 32))==5) {
	        	 System.out.println("Chaos");
	         }else if(Integer.parseInt(str.substring(28, 32))==6) {
	        	 System.out.println("IEEE 802.3 networks");
	         }else if(Integer.parseInt(str.substring(28, 32))==7) {
	        	 System.out.println("ARCNET");
	         }else if(Integer.parseInt(str.substring(28, 32))==8) {
	        	 System.out.println("Hyperchannel");
	         }else if(Integer.parseInt(str.substring(28, 32))==9) {
	        	 System.out.println("Lanstar");
	         }else if(Integer.parseInt(str.substring(28, 32))==10) {
	        	 System.out.println("Autonet Short Address");
	         }else if(Integer.parseInt(str.substring(28, 32))==11) {
	        	 System.out.println("LocalTalk");
	         }else {
	        	 System.out.println("LocalNet");
	         }
			
			System.out.println("  2) Protocol Type : "+str.substring(32, 36)+" /  IP");
			System.out.println("  3) H/W Size : "+str.substring(36, 38)+" /  "+Integer.parseInt(str.substring(36, 38))*8+" bits");
			System.out.println("  4) Protocol Size : "+str.substring(38, 40)+" /  "+Integer.parseInt(str.substring(38, 40))*8+" bits");
			
			System.out.print("  5) Operation : "+str.substring(40, 44)+" /  ");
			if(Integer.parseInt(str.substring(40, 44))==1) {
	            System.out.println(" ARP Request");
	            }else if(Integer.parseInt(str.substring(40, 44))==2) {
		        	 System.out.println("ARP Reply");
		         }
	            else if(Integer.parseInt(str.substring(40, 44))==3) {
		        	 System.out.println(" RARP Request");
		         }else if(Integer.parseInt(str.substring(40, 44))==4) {
		        	 System.out.println("RARP Reply");
		         }else {
		        	 System.out.println("잘못입력..");
		         }
			
			System.out.print("  6) Sender MAC Address : "+str.substring(44,46)+":"+str.substring(46,48)+":"
					 +str.substring(48,50)+":"+str.substring(50,52)+":"+str.substring(52,54)+":"+str.substring(54,56));
			 if(Integer.parseInt(str.substring(44,46),16)%2==0) {
				 System.out.println(" / Unicast");
			 }else {
				 System.out.println("/ Broadcast");
			 }
			 
			 System.out.println("  7) Sender IP Address : "+str.substring(56,64)+" /  "+Integer.parseInt(str.substring(56, 58),16)+"."+
			 Integer.parseInt(str.substring(58, 60),16) +"."+Integer.parseInt(str.substring(60, 62),16)+"."+Integer.parseInt(str.substring(62, 64),16));
			 
			 System.out.println("  8) Target MAC Address : "+str.substring(64,66)+":"+str.substring(66,68)+":"
					 +str.substring(68,70)+":"+str.substring(70,72)+":"+str.substring(72,74)+":"+str.substring(74,76)+" / Unknown MAC");
			 
			 System.out.println("  9) Target IP Address : "+str.substring(76,84)+" /  "+ Integer.parseInt(str.substring(76, 78),16) +"."+
			 Integer.parseInt(str.substring(78, 80),16)+"."+Integer.parseInt(str.substring(80, 82),16)+"."+Integer.parseInt(str.substring(82, 84),16));
		}
		  
		 
		 
	}

	static String bytesToBinaryString(Byte b) {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < 8; i++) {
            builder.append(((0x80 >>> i) & b) == 0 ? '0' : '1');
        }

        return builder.toString();
    }
}