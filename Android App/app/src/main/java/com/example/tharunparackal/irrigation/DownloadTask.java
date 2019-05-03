package com.example.tharunparackal.irrigation;

import android.os.AsyncTask;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import android.util.Log; // used for debugging

/**
 * DownloadTask.java
 *
 * Used to retrieve weather data from the API
 *
 * @author Nick Mussoline, Tharun Parackal
 */

public class DownloadTask extends AsyncTask<String,Void,String>
{

    private static final String TAG = DownloadTask.class.getSimpleName(); // used for debugging
    public static String placeName;
    @Override
    protected String doInBackground(String... urls)
    {
        String result = "";
        URL url;
        HttpURLConnection urlConncetion = null;


        try
        {
            url = new URL(urls [0]);
            Log.d(TAG, "URL CREATED: " + urls[0]);
            urlConncetion = (HttpURLConnection) url.openConnection();

            InputStream in = urlConncetion.getInputStream();
            InputStreamReader reader = new InputStreamReader(in);

            int data = reader.read();

            while(data !=-1) // reads in the weather data from the URL
            {
                char current = (char) data;
                result += current;
                data = reader.read();
            }
            Log.d(TAG, "TRY/CATCH SUCCESSFUL");
            Log.d(TAG, "RESULT: " + result);
            return result;
        }
        catch (Exception e)
        {
            Log.d(TAG, "TRY/CATCH FAILED");
            e.printStackTrace();
        }
        return null;
    }

    @Override
    protected void onPostExecute(String result)
    {
        super.onPostExecute(result);

        try
        {
            JSONObject jsonObject = new JSONObject(result);

//            JSONObject weatherCondition = new JSONObject(jsonObject.getString("weather"));

//            double condition = Double.parseDouble(weatherCondition.getString("main"));

//            Log.v(TAG, "weather status: " + condition); // used for debugging

//            JSONObject weatherData = jsonObject.getJSONObject("weather");

            JSONArray weatherArray = jsonObject.getJSONArray("weather");
            JSONObject weatherData = weatherArray.getJSONObject(0);

//            JSONObject IDData = new JSONObject(weatherData.getString("id"));

//            int condition = Integer.parseInt(jsonObject.getString("id"));
            int condition = Integer.parseInt(weatherData.getString("id")); // retrieves the weather condition ID
//            int temperatureInteger = (int) (temperature * 1.8-459.67);
            Log.d(TAG, "Weather Status: " + condition); // used for debugging


            placeName = jsonObject.getString("name"); // retrieves the geographical location of the zip code
            Log.d(TAG, "Location: " + placeName); // used for debugging


        }
        catch (JSONException e)
        {
            e.printStackTrace();
        }
    }
}

