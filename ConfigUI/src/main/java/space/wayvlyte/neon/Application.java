package space.wayvlyte.config;

import com.google.gson.Gson;

import javax.swing.*;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

public class Application {
    public static void main(String[] args) {
        Gson g = new Gson();

        JFrame frame = new JFrame();
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setSize(300, 600);

        String[] jars = g.fromJson(GetJars(frame), String[].class);
        System.out.println(jars[0]);
    }

    private static String GetJars(JFrame frame) {
        HttpClient client;
        HttpRequest req;
        HttpResponse<String> res = null;

        try {
            client = HttpClient.newHttpClient();
            req = HttpRequest.newBuilder()
                    .uri(URI.create("http://0.0.0.0:5000"))
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
}
