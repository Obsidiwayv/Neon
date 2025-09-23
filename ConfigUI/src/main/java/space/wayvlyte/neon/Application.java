package space.wayvlyte.neon;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.io.File;
import java.io.FileWriter;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.HashMap;

public class Application {
    // Directory where the json database will be created
    private static File directory = new File(
            System.getenv("LOCALAPPDATA") + "/Wayvlyte/Neon");

    public static void main(String[] args) {
        Gson g = new Gson();

        if (directory.mkdirs()) {
            System.out.println("> Created " + directory.getPath() + " Directory");
        }

        JFrame frame = new JFrame();
        frame.setTitle("Neon Selection GUI");

        frame.setLayout(new BorderLayout());
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setSize(500, 600);

        JPanel jarPanel = new JPanel();
        jarPanel.setLayout(new BoxLayout(jarPanel, BoxLayout.Y_AXIS));

        String[] jars = g.fromJson(GetJars(frame), String[].class);

        for (String jar : jars) {
            jarPanel.add(new JCheckBox(jar, true));
        }

        frame.add(new JLabel("Select what will be ignored"), BorderLayout.NORTH);
        frame.add(new JScrollPane(jarPanel), BorderLayout.CENTER);
        JPanel bPanel = new JPanel();
        JButton button = new JButton("Continue");
        button.addActionListener(e -> HandleCheckboxes(e, frame, jarPanel));
        bPanel.add(button);
        frame.add(bPanel, BorderLayout.SOUTH);

        frame.setVisible(true);
    }

    private static String GetJars(JFrame frame) {
        HttpClient client;
        HttpRequest req;
        HttpResponse<String> res = null;

        try {
            client = HttpClient.newHttpClient();
            req = HttpRequest.newBuilder()
                    .uri(URI.create("http://0.0.0.0:5000/list"))
                    .build();
            res = client.send(req, HttpResponse.BodyHandlers.ofString());
        } catch (Exception e) {
            JOptionPane.showMessageDialog(frame,
                    "HttpRequest had an error and will now close.");
        }
        if (res != null) {
            return res.body();
        } else {
            return "EMPTY";
        }
    }

    private static void HandleCheckboxes(ActionEvent e, JFrame frame, JPanel checkboxPanel) {
        HashMap<String, Boolean> selections = new HashMap<String, Boolean>();

        for (Component c : checkboxPanel.getComponents()) {
            if (c instanceof JCheckBox checkBox)
                selections.put(checkBox.getText(), checkBox.isSelected());
        }

        File jsonFile = new File(directory, "jar_database.json");

        Gson g = new GsonBuilder().setPrettyPrinting().create();

        try (FileWriter writer = new FileWriter(jsonFile)) {
            g.toJson(selections, writer);
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(frame,
                    "Could not write json database");
        }

        JOptionPane.showMessageDialog(frame,
                "Completed");
        System.exit(1);
    }
}
