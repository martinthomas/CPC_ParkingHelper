#ifndef DISPLAY_H
#define DISPLAY_H

class Display{
  private:
    bool alert_state = false;
    size_t alert_counter = 0;
    size_t alert_counter_max = 240;
    size_t alert_beats = 0; 
    const unsigned alert_beats_initial = 2;
    unsigned msd = 30;

  public:
    Display(const unsigned minimum_safe_distance){
      msd = minimum_safe_distance;
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

    void displayDistance(size_t distance){
      if (distance < msd)
      {
        alert_state = true;
        displayGraph(10, true);
      } else {
        alert_state = false;
        size_t magnitude = (distance - msd)/10;
        displayGraph(magnitude, false);
      }
    }
    
    void displayGraph(unsigned magnitude, bool alerting){
      if (magnitude > 10){
        magnitude = 10;
      }

      uint32_t color = CircuitPlayground.strip.Color(255, 0, 0); //default is red
      CircuitPlayground.strip.clear();
      
      if (alerting){
        alert_counter ++;
        if (alert_counter > alert_counter_max){  // turn off alert light if on without interruption for 1 mins
          color = CircuitPlayground.strip.Color(0, 0, 0);
        }
        
        if (alert_beats){ // turn on and off 
          alert_beats--;
        } else {
          color = CircuitPlayground.strip.Color(0, 0, 0);
          alert_beats = alert_beats_initial;
        }
      } else {  // no longer alerting, reset beats and counter
        alert_counter = 0;
        color = CircuitPlayground.strip.Color(0, 255, 0);
        if (magnitude <5){
         color = CircuitPlayground.strip.Color(0, 255, 255);
        }
      }
      for(size_t idx =0; idx <= magnitude; idx++){
        CircuitPlayground.strip.setPixelColor(idx, color);
      }
      CircuitPlayground.strip.show();      
    }
};
#endif
