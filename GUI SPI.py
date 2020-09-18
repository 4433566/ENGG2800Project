# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
import tkinter as tk
import time
import serial


def main():
    ser = serial.Serial('COM5',4800,timeout=1) #chose serial port
    root = tk.Tk()

    root.title("GUI RollTimer")
    root.geometry("500x300")

    time_frame = tk.Frame(root)
    time_frame.pack()
    timerlabel = tk.Label(time_frame, text="Current PC time:")
    timerlabel.pack(side=tk.LEFT)
    current_time = tk.Label(time_frame, text="Hello")
    current_time.pack(side=tk.LEFT)

    alarm_frame = tk.Frame(root)
    alarm_frame.pack(side=tk.TOP, anchor=tk.W, pady=10)
    alarm_time = tk.Label(alarm_frame,
                                text="Choose Four Alarm Times? (HH:MM:SS)")
    alarm_time.pack(side=tk.LEFT)
    entry_one = tk.Entry(alarm_frame, width=8)
    entry_one.pack(side=tk.LEFT, padx=5)
    entry_two = tk.Entry(alarm_frame, width=8)
    entry_two.pack(side=tk.LEFT, padx=5)
    entry_three = tk.Entry(alarm_frame, width=8)
    entry_three.pack(side=tk.LEFT, padx=5)
    entry_four = tk.Entry(alarm_frame, width=8)
    entry_four.pack(side=tk.LEFT, padx=5)

    tone_frame = tk.Frame(root)
    tone_frame.pack(side=tk.TOP, anchor=tk.W, pady=10)
    alarm_tone = tk.Label(tone_frame,
                                text="Choose Four Alarm Tones? (kHz:ms)")
    alarm_tone.pack(side=tk.LEFT)
    tone_one = tk.Entry(tone_frame, width=6)
    tone_one.pack(side=tk.LEFT, padx=5)
    tone_two = tk.Entry(tone_frame, width=6)
    tone_two.pack(side=tk.LEFT, padx=5)
    tone_three = tk.Entry(tone_frame, width=6)
    tone_three.pack(side=tk.LEFT, padx=5)
    tone_four = tk.Entry(tone_frame, width=6)
    tone_four.pack(side=tk.LEFT, padx=5)

    selected_mode = tk.Button(root, bd=0,
                                    text="Currently Selected Mode:")
    selected_mode.pack(anchor=tk.W, pady=10)
    accelerometer = tk.Button(root, bd=0,
                                    text="Accelerometer Reading:")
    accelerometer.pack(anchor=tk.W, pady=10)
    temperature = tk.Button(root, bd=0,
                                  text="Temperature Reading:")
    temperature.pack(anchor=tk.W, pady=10)
    humidity = tk.Button(root, bd=0,
                                  text="Humidity Reading:")
    humidity.pack(anchor=tk.W, pady=10)

    def get_current_time():
        newtime = time.strftime("%H:%M:%S")
        current_time.config(text=newtime)
        root.after(200, get_current_time)
        return newtime

    def get_user_alarm_time(alarm_entry):
        user_alarm = alarm_entry.get()
        print(user_alarm)

    get_current_time()

    micro_time = get_current_time()
    ser.write(micro_time.encode())


    #print(ser.read(20))


    root.mainloop()


if __name__ == '__main__':
    main()


