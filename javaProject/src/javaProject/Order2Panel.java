package javaProject;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class Order2Panel extends JPanel {
		
	public JTextArea resultTA = new JTextArea(18,45);
	
	public Order2Panel() {
		
		this.setBackground(Color.CYAN);
		this.add(new JScrollPane(resultTA));
		
		
		
	}

}
