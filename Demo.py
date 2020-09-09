#GUI for RollTimer

import tkinter as tk
import time

class Window(object):
    def __init__(self,master):
        self._master = master
        self._master.title("GUI RollTimer")
        self._master.geometry("500x300")

        self._time_frame = tk.Frame(self._master)
        self._time_frame.pack()
        self._timerlabel = tk.Label(self._time_frame, text="Current PC time:")
        self._timerlabel.pack(side=tk.LEFT)
        self._current_time = tk.Label(self._time_frame, text="Hello")
        self._current_time.pack(side=tk.LEFT)
        
        self._alarm_frame = tk.Frame(self._master)
        self._alarm_frame.pack(side=tk.TOP,anchor=tk.W,pady=10)
        self._alarm_time = tk.Label(self._alarm_frame,
                                    text="Choose Four Alarm Times? (HH:MM:SS)")
        self._alarm_time.pack(side=tk.LEFT)
        self._entry_one = tk.Entry(self._alarm_frame,width=8)
        self._entry_one.pack(side=tk.LEFT,padx=5)
        self._entry_two = tk.Entry(self._alarm_frame,width=8)
        self._entry_two.pack(side=tk.LEFT,padx=5)
        self._entry_three = tk.Entry(self._alarm_frame,width=8)
        self._entry_three.pack(side=tk.LEFT,padx=5)
        self._entry_four = tk.Entry(self._alarm_frame,width=8)
        self._entry_four.pack(side=tk.LEFT,padx=5)

        self._tone_frame = tk.Frame(self._master)
        self._tone_frame.pack(side=tk.TOP,anchor=tk.W,pady=10)
        self._alarm_tone = tk.Label(self._tone_frame,
                                    text="Choose Four Alarm Tones? (kHz:ms)")
        self._alarm_tone.pack(side=tk.LEFT)
        self._tone_one = tk.Entry(self._tone_frame,width=6)
        self._tone_one.pack(side=tk.LEFT,padx=5)
        self._tone_two = tk.Entry(self._tone_frame,width=6)
        self._tone_two.pack(side=tk.LEFT,padx=5)
        self._tone_three = tk.Entry(self._tone_frame,width=6)
        self._tone_three.pack(side=tk.LEFT,padx=5)
        self._tone_four = tk.Entry(self._tone_frame,width=6)
        self._tone_four.pack(side=tk.LEFT,padx=5)

        self._selected_mode = tk.Button(self._master, bd = 0,
                            text="Currently Selected Mode:")
        self._selected_mode.pack(anchor=tk.W,pady=10)
        self._accelerometer = tk.Button(self._master, bd = 0,
                                text="Accelerometer Reading:")
        self._accelerometer.pack(anchor=tk.W,pady=10)
        self._temperature = tk.Button(self._master, bd = 0,
                                  text="Temperature Reading:")
        self._temperature.pack(anchor=tk.W,pady=10)
        self._humidity = tk.Button(self._master, bd = 0,
                                  text="Humidity Reading:")
        self._humidity.pack(anchor=tk.W,pady=10)
        
        self.get_current_time()
        
        
    def get_current_time(self):
        self.time = time.strftime("%H:%M:%S")
        self._current_time.config(text=self.time)
        root.after(200, self.get_current_time)
        
root = tk.Tk()
window = Window(root)
root.mainloop()
