package com.example.tharunparackal.irrigation;

import android.os.AsyncTask;
import org.json.JSONException;
import org.json.JSONObject;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import android.util.Log; // used for debugging

public class DownloadTask extends AsyncTask<String,Void,String> {

    private static final String TAG = DownloadTask.class.getSimpleName(); // used for debugging

    @Override
    protected String doInBackground(String... urls) {
        String result = "";
        URL url;
        HttpURLConnection urlConncetion = null;


        try {
            url = new URL(urls [0]);

            urlConncetion = (HttpURLConnection) url.openConnection();

            InputStream in = urlConncetion.getInputStream();
            InputStreamReader reader = new InputStreamReader(in);

            int data = reader.read();

            while(data !=-1)
            {
                char current = (char) data;
                result += current;
                data = reader.read();
            }
            return result;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    protected void onPostExecute(String result){
        super.onPostExecute(result);

        try {
            JSONObject jsonObject = new JSONObject(result);

            JSONObject weatherCondition = new JSONObject(jsonObject.getString("weather"));

            double condition = Double.parseDouble(weatherCondition.getString("main"));

            Log.v(TAG, "weather status: " + condition); // used for debugging

            JSONObject weatherData = new JSONObject(jsonObject.getString("main"));

            double temperature = Double.parseDouble(weatherData.getString("temp"));
            int temperatureInteger = (int) (temperature * 1.8-459.67);

            String placeName = jsonObject.getString("name");

        } catch (JSONException e) {
            e.printStackTrace();
        }
    }
}

