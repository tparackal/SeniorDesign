package com.example.tharunparackal.irrigation;


import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.Toast;



public class ZoneActivity extends AppCompatActivity implements AdapterView.OnItemSelectedListener {
    public Spinner soilSpinner1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_zone);

        soilSpinner1 = findViewById(R.id.spinner);
        ArrayAdapter<CharSequence> soilTypeAdapter = ArrayAdapter.createFromResource(this, R.array.soilType, android.R.layout.simple_spinner_item);
        soilTypeAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        soilSpinner1.setAdapter(soilTypeAdapter);
        soilSpinner1.setOnItemSelectedListener(this);

        Spinner soilSpinner2 = findViewById(R.id.spinner3);
        ArrayAdapter<CharSequence> playerAdapter = ArrayAdapter.createFromResource(this, R.array.soilType, android.R.layout.simple_spinner_item);
        playerAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        soilSpinner2.setAdapter(playerAdapter);
        soilSpinner2.setOnItemSelectedListener(this);

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