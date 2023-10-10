import tkinter as tk
import serial


arduino_port = 'COM3'  # Arduino Port

root = tk.Tk()
root.title("Servo Control")

servo_angles = [90, 90, 90]


def update_servo_position(servo_num, value):
    try:
        angle = int(value)
        if 0 <= angle <= 180:
            arduino.write(f"{servo_num} {angle}\n".encode())
            servo_angles[servo_num] = angle
    except ValueError:
        pass

sliders = []
for i in range(3):
    label = tk.Label(root, text=f"Servo {i}")
    label.pack()
    slider = tk.Scale(root, from_=0, to=180, orient='horizontal', label='Servo Angle',
                      length=300, command=lambda val, servo_num=i: update_servo_position(servo_num, val))
    slider.set(servo_angles[i])
    slider.pack()
    sliders.append(slider)

try:
    arduino = serial.Serial(arduino_port, 9600, timeout=1)
except serial.SerialException:
    print("Failed to open serial connection to Arduino")
    exit(1)

def quit_program():
    arduino.close()
    root.quit()

quit_button = tk.Button(root, text="Quit", command=quit_program)
quit_button.pack()

root.mainloop()
