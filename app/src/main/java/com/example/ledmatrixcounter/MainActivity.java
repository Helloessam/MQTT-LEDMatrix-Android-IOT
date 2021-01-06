package com.example.ledmatrixcounter;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.CountDownTimer;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.io.UnsupportedEncodingException;
import java.util.Locale;
import java.util.concurrent.TimeUnit;

public class MainActivity extends AppCompatActivity {
    ImageButton CounterON,CounterOFF ;
    TextView Counter ;
    Button Submit ;
    EditText SubmitTxt;
    int starNumber = 10;
    CountDownTimer countDownTimer;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
         CounterON= (ImageButton) findViewById(R.id.onButton);
         CounterOFF= (ImageButton) findViewById(R.id.offButton);
         Counter = (TextView) findViewById(R.id.CounterValue);
        Submit = (Button) findViewById(R.id.SubmitBtn);
        SubmitTxt = (EditText) findViewById(R.id.SubTxt);
        Counter_connect();
    }

    public void time_Counter() {
         long Duration = TimeUnit.SECONDS.toMillis(10);
         new CountDownTimer(Duration,1000) {

            @Override
            public void onTick(long millisUntilFinished) {

                Counter.setText(Long.toString(millisUntilFinished/1000));
            }

            @Override
            public void onFinish() {
                Counter.setVisibility(View.GONE);
            }
        }.start();
    }

    public void Counter_connect()
    {
        String clientId = MqttClient.generateClientId();
        MqttConnectOptions options = new MqttConnectOptions();
        final MqttAndroidClient client =
                new MqttAndroidClient(MainActivity.this, "tcp://broker.hivemq.com:1883",
                        clientId);

        try {
            options.setUserName("emmy");
            options.setPassword("batates".toCharArray());

            IMqttToken token = client.connect(options);
            token.setActionCallback(new IMqttActionListener() {
                @Override
                public void onSuccess(IMqttToken asyncActionToken) {

                    CounterON.setOnClickListener(new View.OnClickListener() {
                        @Override
                        public void onClick(View v) {
                            time_Counter();
                            String topic = "inMatrix";
                            String payload = "?";
                            byte[] encodedPayload = new byte[0];
                            try {
                                encodedPayload = payload.getBytes("UTF-8");
                                MqttMessage message = new MqttMessage(encodedPayload);
                                client.publish(topic, message);
                            } catch (UnsupportedEncodingException | MqttException e) {
                                e.printStackTrace();
                            }
                        }
                    });


                    Submit.setOnClickListener(new View.OnClickListener() {
                        @Override
                        public void onClick(View v) {
                            String object = SubmitTxt.getText().toString();
                            String topic = "inMatrix";
                            String payload = object ;
                            byte[] encodedPayload = new byte[0];
                            try {
                                encodedPayload = payload.getBytes("UTF-8");
                                MqttMessage message = new MqttMessage(encodedPayload);
                                client.publish(topic, message);
                            } catch (UnsupportedEncodingException | MqttException e) {
                                e.printStackTrace();
                            }
                        }
                    });

                    CounterOFF.setOnClickListener(new View.OnClickListener() {
                        @Override
                        public void onClick(View v) {

                            String topic = "inMatrix";
                            String payload = "+";
                            byte[] encodedPayload = new byte[0];
                            try {
                                encodedPayload = payload.getBytes("UTF-8");
                                MqttMessage message = new MqttMessage(encodedPayload);
                                client.publish(topic, message);
                            } catch (UnsupportedEncodingException | MqttException e) {
                                e.printStackTrace();
                            }

                        }
                    });
                    Toast.makeText(MainActivity.this,"Connected",Toast.LENGTH_LONG).show();

    }
    

}
