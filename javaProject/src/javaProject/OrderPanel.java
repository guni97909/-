package javaProject;

import java.awt.Color;
import java.awt.TextArea;
import java.util.Vector;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.table.DefaultTableModel;

public class OrderPanel extends JPanel {
	String header[] = {"품목", "수량", "판매금액"};
	   public DefaultTableModel model = new DefaultTableModel(header, 0);
	   public JTable table = new JTable(model);
	  
	   
	   public coffee cfGUI;
	
	public OrderPanel(coffee coffeeDBGUI)	{
		this.cfGUI = coffeeDBGUI;
		JScrollPane sp = new JScrollPane(table);
		this.setBackground(Color.CYAN);
	      this.add(sp);		 
	}

}
