#ifndef DISPLAY_H
#define DISPLAY_H

class Display{
  private:
  
    bool alert_state = false;
    size_t display_counter = 0;
    size_t display_counter_max = 100;
    size_t alert_beats = 0; 
    const unsigned alert_beats_initial = 2;
    unsigned msd = 30;
    size_t last_magnitude = 0;
    
  public:
    Display(){
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

    void displayDistance(size_t distance, const unsigned int thresh){
      if (distance < thresh)
      {
        alert_state = true;
        displayGraph(10, true);
      } else {
        alert_state = false;
        size_t magnitude = (distance - thresh)/10;
        displayGraph(magnitude, false);
      }
    }
    
    void displayGraph(unsigned magnitude, bool alerting){

      bool display_on = true;
      CircuitPlayground.strip.clear();      
      uint32_t color = CircuitPlayground.strip.Color(255, 0, 0); //default is red
      
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
          color = CircuitPlayground.strip.Color(0, 0, 0);
          display_on = false;
          Serial.println("Display OFF");
        }
      }

      // pick color to display depending on if alerting or not
      if (display_on){
        if (alerting){
          if(alert_beats){ // turn on and off 
            alert_beats--;
          } else {
            color = CircuitPlayground.strip.Color(0, 0, 0);
            alert_beats = alert_beats_initial;
          }
        } else {        
          color = CircuitPlayground.strip.Color(0, 255, 0);
          if (magnitude <5){
           color = CircuitPlayground.strip.Color(0, 255, 255);
          }
        }

        for(size_t idx =0; idx <= magnitude; idx++){
          CircuitPlayground.strip.setPixelColor(idx, color);
        }
      }
      CircuitPlayground.strip.show();      
    }
};
#endif
