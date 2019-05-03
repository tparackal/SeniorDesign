package com.example.tharunparackal.irrigation;


import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.Toast;
import android.widget.TextView;
import android.util.Log;

/**
 * ZoneActivity.java
 *
 * Contains window used to manage zones
 *
 * @author Tharun Parackal
 */


public class ZoneActivity extends AppCompatActivity implements AdapterView.OnItemSelectedListener {
    public Spinner soilSpinner1, soilSpinner2, soilSpinner3, moistureSpinner1, moistureSpinner2, moistureSpinner3;

    private static final String TAG = ZoneActivity.class.getSimpleName(); // used for debugging


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_zone);
//Soil Spinners
        soilSpinner1 = findViewById(R.id.spinner);
        ArrayAdapter<CharSequence> soilType1Adapter = ArrayAdapter.createFromResource(this, R.array.soilType, android.R.layout.simple_spinner_item);
        soilType1Adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        soilSpinner1.setAdapter(soilType1Adapter);
        soilSpinner1.setOnItemSelectedListener(this);

        soilSpinner2 = findViewById(R.id.spinner2);
        ArrayAdapter<CharSequence> soilType2Adapter = ArrayAdapter.createFromResource(this, R.array.soilType, android.R.layout.simple_spinner_item);
        soilType2Adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        soilSpinner2.setAdapter(soilType2Adapter);
        soilSpinner2.setOnItemSelectedListener(this);

        soilSpinner3 = findViewById(R.id.spinner3);
        ArrayAdapter<CharSequence> soilType3Adapter = ArrayAdapter.createFromResource(this, R.array.soilType, android.R.layout.simple_spinner_item);
        soilType3Adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        soilSpinner3.setAdapter(soilType3Adapter);
        soilSpinner3.setOnItemSelectedListener(this);

//Moisture Spinners

        moistureSpinner1 = findViewById(R.id.MoistureLevel1);
        ArrayAdapter<CharSequence> moistureType1Adapter = ArrayAdapter.createFromResource(this, R.array.moistureLevel, android.R.layout.simple_spinner_item);
        moistureType1Adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        moistureSpinner1.setAdapter(moistureType1Adapter);
        moistureSpinner1.setOnItemSelectedListener(this);

        moistureSpinner2 = findViewById(R.id.MoistureLevel2);
        ArrayAdapter<CharSequence> moisture2Adapter = ArrayAdapter.createFromResource(this, R.array.moistureLevel, android.R.layout.simple_spinner_item);
        moisture2Adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        moistureSpinner2.setAdapter(moisture2Adapter);
        moistureSpinner2.setOnItemSelectedListener(this);

        moistureSpinner3 = findViewById(R.id.MoistureLevel3);
        ArrayAdapter<CharSequence> moisture3Adapter = ArrayAdapter.createFromResource(this, R.array.moistureLevel, android.R.layout.simple_spinner_item);
        moisture3Adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        moistureSpinner3.setAdapter(moisture3Adapter);
        moistureSpinner3.setOnItemSelectedListener(this);

        String location = DownloadTask.placeName;
        TextView text = (TextView) findViewById(R.id.Location);
        text.setText(location);



    }

    @Override
    public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
        String text = parent.getItemAtPosition(position).toString();
        Toast.makeText(parent.getContext(), text, Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onNothingSelected(AdapterView<?> parent) {

    }

}