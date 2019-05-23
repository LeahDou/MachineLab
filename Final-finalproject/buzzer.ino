
boolean onplaying = false;


// TONES  ==========================================
// Start by defining the relationship between
//       note, period, &  frequency.
#define  c     3830    // 261 Hz 
#define  d     3400    // 294 Hz 
#define  e     3038    // 329 Hz 
#define  f     2864    // 349 Hz 
#define  x     3000    // try to create the note 4*
#define  g     2550    // 392 Hz 
#define  a     2272    // 440 Hz 
#define  b     2028    // 493 Hz 
#define  C     1912    // 523 Hz 
#define  y     0 // 0Hz, the note to stop playing until the switch is on 
// Define a special note, 'R', to represent a rest
#define  R     0

// SETUP ============================================
// Set up speaker on a PWM pin (digital 9, 10 or 11)
int speakerOut = 9;
// Do we want debugging on serial out? 1 for yes, 0 for no
int DEBUG = 1;

void setup() {
  pinMode( 6, INPUT);// the switch
  pinMode(speakerOut, OUTPUT);
  if (DEBUG) {
    Serial.begin(9600); // Set serial out if we want debugging
  }
}

// MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[],
//  which sets each note's relative length (higher #, longer note)
int melody[] = { d,e,e,e,e,e,e,e,e,e,e,e,e,e,e,d,e,d,e,a,g,g,d,e,e,e,d,e,d,e,e,e,d,d,d,d,b,a,g,e,e,b,d,g,x,e,d,e,e,g,x,e,d,e,e};// this is a horrible composing but I am not a musical student and I tried my best
int beats[]  = { 16,16,16,64,64,32,64,64,16,16,16,64,64,32,32,64,64,64,32,64,64,64,32,64,64,64,64,64,128,32,62,62,62,62,32,64,64,32,64,128,128,128,64,64,128,128,128,128,64,64,128};
int melodystop[] = {y};// stop playing
int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.

// Set overall tempo
long tempo = 10000;
// Set length of pause between notes
int pause = 4000;
// Loop variable to increase Rest length
int rest_count = 40000; //<-BLETCHEROUS HACK; See NOTES

// Initialize core variables
int tone_ = 0;
int beat = 0;
long duration  = 0;

// PLAY TONE  ==============================================
// Pulse the speaker to play a tone for a particular duration
void playTone() {

  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut, HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    }
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);
    }
  }
}

// LET THE WILD RUMPUS BEGIN =============================
void loop() {
  int onplay;
  if (onplay !=1) {
    onplay = digitalRead(6);
  }
  Serial.println(onplay);
  if (onplay == 1) { .  // if switch is on
    // Set up a counter to pull from melody[] and beats[]
    for (int i = 0; i < MAX_COUNT; i++) {
      tone_ = melody[i];
      beat = beats[i];

      duration = beat * tempo; // Set up timing

      playTone();
      // A pause between notes...
      delayMicroseconds(pause);

      if (DEBUG) { // If debugging, report loop, tone, beat, and duration
        Serial.print(i);
        Serial.print(":");
        Serial.print(beat);
        Serial.print(" ");
        Serial.print(tone_);
        Serial.print(" ");
        Serial.println(duration);
      }
    }
  }
  else if (onplay == 0) { // is switch is off, so that the buzzer will not playing the melody until the switch is on
    for (int i = 0; i < MAX_COUNT; i++) {
      tone_ = melodystop[i];
      beat = beats[i];

      duration = beat * tempo; // Set up timing

      playTone();
      // A pause between notes...
      delayMicroseconds(pause);

      if (DEBUG) { // If debugging, report loop, tone, beat, and duration
        Serial.print(i);
        Serial.print(":");
        Serial.print(beat);
        Serial.print(" ");
        Serial.print(tone_);
        Serial.print(" ");
        Serial.println(duration);
      }
    }
  }


}

