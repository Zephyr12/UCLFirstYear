#define NUM_SENSORS 3

#define TEMP_SENSOR P1_0
#define RPM_SENSOR P1_5
#define PH_SENSOR P1_4

#define TEMP_ACTUATOR P1_6
#define RPM_MOTOR P2_2
#define PH_ACID_PUMP P2_0
#define PH_ALKALI_PUMP P2_3

#include<stdlib.h>
#include<string.h>
long COUNT;
int PHOTOINTERRUPTER_STATE;
long LAST_TIME;

struct sensor {
    char* name;
    float target_value;
    uint8_t input_pin;
    float most_recent_value;
    float (*input_to_value) (int);
    void (*regulate_output) (struct sensor*);
};

struct sensor* new_sensor(
    char* name,
    float target_value,
    uint8_t input_pin,
    uint8_t* output_pins,
    int num_output_pins,
    float (*input_to_value) (int),
    void (*regulate_output) (struct sensor*)
    ){
    struct sensor* s = (struct sensor*) malloc(sizeof(struct sensor));
    s->name = name;
    s->target_value = target_value;
    s->input_pin = input_pin;
    s->most_recent_value = 0;
    s->input_to_value = input_to_value;
    s->regulate_output = regulate_output;
    pinMode(s->input_pin, INPUT);
    for(int i = 0; i < num_output_pins; i++){
        pinMode(output_pins[i], OUTPUT);
    }
    return s;
}


struct sensor** sensors;

char* extract_message(String text, char* header, char* buf){
    text.toCharArray(buf, text.length() + 1);
    return (buf + strlen(header)); 
    // shift the buffer by the length of the header
    // also f*** the memory requirements that mean I have 
    // to do this.
}

struct sensor* get_sensor_with_name(char* name){
    for (int i = 0; i < NUM_SENSORS; i++){
        if(strcmp(sensors[i]->name, name) == 0){
            return sensors[i];
        }
    }
    return NULL;
}

void handle_serial(){
    String string = Serial.readStringUntil('\n');
    string.trim();
    char* buffer = (char*) malloc(50 * sizeof(char));
    if(string.startsWith("GET ")){
        char* sensor_name = extract_message(string, "GET ", buffer);
        struct sensor* s = get_sensor_with_name(sensor_name);
        if (s != NULL){
            Serial.print("GET ");
            Serial.print(s->name);
            Serial.print(" ");
            Serial.println(s->most_recent_value);
        }else{
            Serial.println("GET FAILED");
        }
    }
    else if(string.startsWith("INFO ")){
        char* sensor_name = extract_message(string, "INFO ", buffer);
        struct sensor* s = get_sensor_with_name(sensor_name);
        if (s != NULL){
            Serial.print("INFO ");
            Serial.print(s->name);
            Serial.print(" ");
            Serial.println(s->target_value);
        }
        else{
            Serial.println("INFO FAILED");
        }
    }
    else if(string.startsWith("SET ")){
        char* msg = extract_message(string, "SET ", buffer);
        char* sensor_name = strtok(msg, " ");
        struct sensor* s = get_sensor_with_name(sensor_name);
        if (s != NULL){
            char* sensor_value = strtok(NULL, " ");
            float sensor_value_float = String(sensor_value).toFloat();
            s->target_value = sensor_value_float;
            Serial.print("SET ");
            Serial.print(sensor_name);
            Serial.print(" ");
            Serial.println(s->target_value);
        }
        else{
            Serial.println("SET FAILED");
        }
    }
    free(buffer);
}

void handle_sensor(struct sensor* s){
    s->most_recent_value = s->input_to_value(analogRead(s->input_pin));
    s->regulate_output(s);
}

void handle_sensors(){
    for (int i = 0; i < NUM_SENSORS; i++){
        struct sensor* s = sensors[i];
        handle_sensor(s);
    }
}

/* Heater Team's work */
float temp_input_to_value(int value){
    return (float)(4*((value-607)/(43.0f)) + 33);
}

void temp_regulate_output(struct sensor* s){
    if(s->most_recent_value < s->target_value - 2.8){
        analogWrite(TEMP_ACTUATOR, 255);
    }else{
        analogWrite(TEMP_ACTUATOR, 0);
    }
}


/* pH Team's work */
float ph_input_to_value(int value){
    return (float)value;
}
void ph_regulate_output(struct sensor* s){
    float ph_buffer = 0.5;
    if (s->most_recent_value < s->target_value - ph_buffer){
        digitalWrite(PH_ALKALI_PUMP, HIGH);
    } else if (s->most_recent_value > s->target_value + ph_buffer){
        digitalWrite(PH_ACID_PUMP, HIGH);
    } else {
        digitalWrite(PH_ACID_PUMP, LOW);
        digitalWrite(PH_ALKALI_PUMP, LOW);
    }
}

void addToCount(){
    COUNT += 1;
}

/* Motor Team's work*/
float motor_input_to_value(int value){
    int NEW_PHOTOINTERRUPTER_STATE = value > 500 ? 1 : 0;
    if (PHOTOINTERRUPTER_STATE == 1 && NEW_PHOTOINTERRUPTER_STATE == 0){
        // Falling
        COUNT += 1;
    }
    if (LAST_TIME - millis() > 16){
        return COUNT;
    }else{
    }
}

void motor_regulate_output(struct sensor* s){
    analogWrite(RPM_MOTOR, s->target_value);
}

void setup(){
    uint8_t temp_output = TEMP_ACTUATOR;
    uint8_t ph_outputs[2] = {PH_ACID_PUMP, PH_ALKALI_PUMP};
    uint8_t motor_output = RPM_MOTOR;
    sensors = (struct sensor**) malloc(sizeof(struct sensor*) * NUM_SENSORS);
    sensors[0] = new_sensor("Temp", 35.0f, TEMP_SENSOR, &temp_output, 1, &temp_input_to_value, &temp_regulate_output);
    sensors[1] = new_sensor("pH", 5.0f, PH_SENSOR, ph_outputs, 2, &ph_input_to_value, &ph_regulate_output);
    sensors[2] = new_sensor("Motor", 0.0f, RPM_SENSOR, &motor_output, 1, &motor_input_to_value, &motor_regulate_output);
    Serial.begin(9600);
    Serial.setTimeout(16);
    //attachInterrupt(RPM_SENSOR, addToCount, RISING);
}

void loop(){
    handle_sensors();
    if (Serial.available() > 0){
        handle_serial();
    }
    delay(16);
}
