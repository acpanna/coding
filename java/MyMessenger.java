import java.io.*;
import java.awt.*;
import java.awt.event.*;
import java.net.InetAddress;
import java.util.Properties;
import java.util.Date;
import javax.mail.*;
import javax.mail.internet.*;

public class MyMessager
{
    public static void main(String[] argv)
    {
        MyFrame fenster = new MyFrame("HaanerMail");

        fenster.setSize(400,400);
        fenster.setBackground(Color.lightGray);

        fenster.setVisible(true);
    }
}

class MyFrame extends Frame implements WindowListener, ActionListener, KeyListener
{
    private Button button;
    private TextField wer;
    private TextArea was;
    private Label status, mess, name;
    private Container cont1, cont2;

    private String to = "haaner@gmx.de", subject = "HomePage - Message", mailhost = "mx.freenet.de", mailer = "HaanerMail";
   	private StringBuffer from;

    private boolean typed;

    public MyFrame()
    {
        this("");
    }

    public MyFrame(String titel)
    {
        super(titel);

        button = new Button("Message abschicken");

        wer = new TextField();
        was = new TextArea();

        status = new Label("Status: Alles Roger in Kambodscha", Label.CENTER);
        name   = new Label("Hier deine EMail - Adresse eingeben:", Label.CENTER);
        mess   = new Label("Hier deine Message eingeben:", Label.CENTER);

        typed = false;

        cont1 = new Container();
        cont2 = new Container();

        cont1.setLayout(new BorderLayout());
        cont2.setLayout(new BorderLayout());

        cont1.add(name, "North");
        cont1.add(wer, "South");
        cont2.add(mess, "North");
        cont2.add(was, "Center");
        cont2.add(button, "South");

        addWindowListener(this);
        button.addActionListener(this);
        was.addKeyListener(this);
        wer.addKeyListener(this);

        add(cont1, "North");
        add(cont2, "Center");
        add(status, "South");
    }

    public void windowActivated(WindowEvent e)
    {}
    public void windowClosed(WindowEvent e)
    {}
    public void windowClosing(WindowEvent e)
    {
         dispose();
         System.exit(0);
    }
    public void windowDeactivated(WindowEvent e)
    {}
    public void windowDeiconified(WindowEvent e)
    {}
    public void windowIconified(WindowEvent e)
    {}
    public void windowOpened(WindowEvent e)
    {}
    public void keyPressed(KeyEvent e)
    {}
    public void keyReleased(KeyEvent e)
    {}
    public void keyTyped(KeyEvent e)
    {
        if (typed == false)
          status.setText("Status: Alles Roger in Kambodscha");

        typed = true;
    }

    public void actionPerformed(ActionEvent evt)
    {
        if (evt.getSource() == button && typed == true)
        {
            from = new StringBuffer((wer.getText()).trim());

            try
            {
                Properties props = System.getProperties();
        	    props.put("mail.smtp.host", mailhost);

        	    Session session = Session.getDefaultInstance(props, null);

        	    Message msg = new MimeMessage(session);

        	    msg.setFrom(new InternetAddress(from.toString()));
        	    msg.setRecipients(Message.RecipientType.TO, InternetAddress.parse(to, false));
        	    msg.setSubject(subject);

        	    msg.setText(was.getText());

        	    msg.setHeader("X-Mailer", mailer);
        	    msg.setSentDate(new Date());

        	    Transport.send(msg);

                status.setText("Status: Message erfolgreich gesendet ...");
            }

            catch(AddressException exc)
    	    {
 	            status.setText("Status: EMail - Adresse ungueltig, Message wurde nicht gesendet ...");
 	        }

 	        catch(Exception exc)
 	        {
 	             status.setText("Status: Ausnahme aufgetreten, Message wurde nicht gesendet ...");
 	        }

       	    typed = false;
        }
    }
}
