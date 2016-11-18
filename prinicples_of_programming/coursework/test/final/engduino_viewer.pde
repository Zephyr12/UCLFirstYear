/*
 * Author: Amartya Vadlamani
 * Notes: Used the java camelCase and the standard processing indentation
 * scheme as this was what made the most sense.
 */

import processing.serial.*;
import java.util.Collections;

class Graph{ 
  private String label;
  
  private float x,y,h,w;
  
  private float red, green, blue;
  
  private float minValue, maxValue;
  
  private ArrayList<Float> values;
  
  Graph(String label, float xPos, float yPos, float graphHeight, float graphWidth, int red, int green, int blue){
    // I prefer C++ constructors, they needed a lot less boilerplate
    this.label = label;
    this.x = xPos;
    this.y = yPos;
    this.h = graphHeight;
    this.w = graphWidth;
    this.red = red;
    this.green = green;
    this.blue = blue;
    this.minValue = 0;
    this.maxValue = 0;
    this.values = new ArrayList<Float>();
  }
  
  public void addPoint(float value){
    /*
     * Add a new floating point value `value` to the graph to be plotted.
     */
     
    
    this.values.add(value);

    this.trimValues((int)(this.w - this.x));
    //discard old values
    
    //update min and max values so the graph knows how to scale and plot the values
    if(value > this.maxValue){
      this.maxValue = value;
    }else if (value < this.minValue){
      this.minValue = value;
    }

  }
  
  void trimValues(int numValues){
    /*
     * Discards values from the start of the graph until only
     * `numValues` values are left
     */
    int numToRemove = this.values.size() - numValues;
    for (int i = 0; i < numToRemove; i++){
      this.values.remove(i);
    }
  }
  
  float transformY(float y){
    /*
     * Turns a floating point value into the offset that is needed to find 
     * the values place on the graph
     * Note: Kinda wishing java had `inline` now.
     */
    return ((y-this.minValue) / (this.maxValue - this.minValue)) * h;
  }
  
  void draw(){

    fill(255);
    stroke(255);

    textSize(10);
    
    // draw the y-axis
    line(this.x, this.y + this.h, this.x, this.y);

    // label the graph
    text(this.label, this.x - 120, this.y + (this.h/2));
    
    //draw the x-axis in a darker color
    stroke(150);
    line(this.x, this.y + this.h - this.transformY(0), this.w, this.y + this.h - this.transformY(0));
    
    //draw the graph in the graphs color
    stroke(this.red, this.green, this.blue);
    
    /*
     * Iterate through values and plot the graph. The scoping block is used to
     * prevent the values of xOffset and lastValue from leaking
     */
    {
      int xOffset = 0;
      float lastValue = 0;
      for(float value : this.values){
        line(this.x+xOffset-1, this.y + this.h - this.transformY(lastValue), this.x+xOffset, this.y + this.h - this.transformY(value));
        lastValue = value;
        xOffset ++;
      }
    }

    stroke(255);

    // label the min, max and zero points on the graph
    text(String.valueOf(this.maxValue), this.x - 40, this.y);
    if (this.values.size() > 0){
      float value = this.values.get(this.values.size() - 1);
      text(String.valueOf(value), this.x + this.values.size() + 20, this.y + this.h - this.transformY(value));
    }
    text("0", this.x - 40, this.y + this.h - this.transformY(0));
    if(this.minValue != 0){
      text(String.valueOf(this.minValue), this.x - 40, this.y + this.h);
    }
  }
}

/*
 * I know global variables are bad but short of wrapping the whole program 
 * in an object there isn't really anyway to avoid these ones, and that doesn't
 * seem to be the processing style of programming
 */
 
Serial myPort;  // The serial port
HashMap<String, Graph> graphs;

void setup() {
  size(1000, 1000);
  surface.setResizable(false);
  graphs = new HashMap<String, Graph>();
  
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[0], 115200);
  myPort.clear();
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  myPort.readStringUntil('\n');
}

void draw() {

  while (myPort.available() > 0) {
    fill(50,200);
    rect(0,0,width,height);
    fill(255);
    int i = 0;
    String updateLine = myPort.readStringUntil('\n');
    
    if (updateLine != null && updateLine.split("=").length == 11) {
      /*
       * Full lines only i.e. lines with 10 '=' signs and so 11 splits
       * Also the null check is needed as otherwise the other check is 
       * a NullReference and so kills the program with an exception
       */

      String[] keyValueList = updateLine.split(","); // split the string into a list of key=value pairs
      
      
      for (String keyValueString : keyValueList){
        i ++;
        String[] keyValuePair = keyValueString.split("="); // split the key=value pairs
        String key = keyValuePair[0];
        float value = Float.parseFloat(keyValuePair[1]);
        
        if (graphs.containsKey(key)){ // if a  graph already exists with this value
          graphs.get(key).addPoint(value); // stick the value on the graph
        }else { //otherwise
          // make a new graph
          Graph g = new Graph(key, 150, 100*graphs.size() + 10, 70, width-50, (i*124 % 125) + 125, (i*i % 125) + 125, (i*i*i % 125) + 125);
          // and then stick on the graph
          g.addPoint(value);
          // and register the graph so you dont keep making new graphs
          graphs.put(key, g);
        }
      }
      for (Graph graph: graphs.values()){
        // yay for abstractions
        graph.draw();
      }
    }
  }
}