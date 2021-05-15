#ifndef DISPLAY_H
#define DISPLAY_H

class Display{
  private:
    enum alert_state_t {NONE=0, CLOSE, DONK } alert_state;
    size_t display_counter = 0;
    size_t display_counter_max = 150;
    size_t alert_beats = 0; 
    const unsigned alert_beats_initial = 4;
    
    float scary_close = 30;
    
    size_t last_magnitude = 0;
    
    uint32_t ALERT_COL = CircuitPlayground.strip.Color(255, 0, 0);
    uint32_t DARK_COL = CircuitPlayground.strip.Color(0, 0, 0);
    uint32_t CLOSE_COL = CircuitPlayground.strip.Color(0, 255, 0);
    uint32_t FAR_COL = CircuitPlayground.strip.Color(0, 255, 255);
    
  public:
    Display(const unsigned int scary_val) : scary_close(scary_val){
      alert_beats = alert_beats_initial;
    }
    
    ~Display(){}
    
    void start()
    {
      CircuitPlayground.setBrightness(60);

      for (unsigned idx=0; idx < 10; idx++){
        CircuitPlayground.strip.setPixelColor(idx, 0);
      }
      CircuitPlayground.strip.show();
    }

    void displayDistance(float distance, const float thresh){
      if (distance < thresh)
      {
        alert_state = CLOSE;
        if (distance < scary_close){
           alert_state = DONK;
        }
        displayGraph(10);
      } else {
        alert_state = NONE;
        size_t magnitude = (distance - thresh)/10;
        displayGraph(magnitude);
      }
    }

    void setManyPixels(uint32_t color, const unsigned int magnitude){
      for(size_t idx =0; idx <= magnitude; idx++){
        CircuitPlayground.strip.setPixelColor(idx, color);
      }
    }
    
    void displayGraph(unsigned int magnitude){

      bool display_on = true;
      CircuitPlayground.strip.clear();      
      uint32_t color = ALERT_COL;
      
      if (magnitude > 10){
        magnitude = 10;
      }

      if (last_magnitude != magnitude)
      {
        last_magnitude = magnitude;
        display_counter = 0;
      } else { // same distance, update counter and check limit
        display_counter ++;
        if (display_counter > display_counter_max){  // turn off light if on without interruption for 1 mins
          color = DARK_COL;
          display_on = false;
        }
      }

      // pick color to display depending on if alerting or not
      if (display_on){
        if (alert_state == NONE){
          color = FAR_COL;
          if (magnitude <5){
            color = CLOSE_COL;
          }
          setManyPixels(color, magnitude);
          
        } else { //  in alert state
          if (alert_state == CLOSE){
            if(alert_beats){ // turn on and off 
              alert_beats--;
            } else {
              color = DARK_COL;
              alert_beats = alert_beats_initial;
            }
          setManyPixels(color, magnitude);
          } else { /* if alert state == DONK */ 
            int32_t offset = millis() / 5;
            // Loop through each pixel and set it to an incremental color wheel value.
            for(int i=0; i<10; ++i) {
              CircuitPlayground.strip.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / 10) + offset) & 255));
            }
            CircuitPlayground.strip.show();
          }
        }
      }
      CircuitPlayground.strip.show();      
    }
};
#endif
