#ifndef DISPLAY_H
#define DISPLAY_H

class Display{
  public:
    Display(){}
    ~Display(){}
    void start()
    {
      CircuitPlayground.setBrightness(60);
      for (int idx=0; idx < 10; idx++){
        CircuitPlayground.strip.setPixelColor(idx, 0);
      }
      CircuitPlayground.strip.show();
    }
    void graph(unsigned magnitude, uint32_t c){
      Serial.print("magnitude ");
      Serial.println(magnitude);
      if (magnitude > 10){
        c = 0;
        magnitude = 10;
      }
      CircuitPlayground.strip.clear();
      for(int idx =0; idx <= magnitude; idx++){
        CircuitPlayground.strip.setPixelColor(idx, c);
      }
      CircuitPlayground.strip.show();
      
    }

    void alert(){
      graph(10, CircuitPlayground.strip.Color(255,0,0));
    }
};
#endif
