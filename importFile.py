import tkinter as tk
from tkinter import filedialog
import shutil
import os
import sys

compress_pressed = False  # Flag to ensure file selection happens only once
file_path = ""

def select_and_copy_file():
     global compress_pressed
     global file_path
    # Check if the file has already been selected
     if not compress_pressed:
        # Prompt the user to select a PDF file
        file_path = filedialog.askopenfilename(filetypes=[("PDF files", "*.pdf")])

        # Check if a file was selected or if the dialog was closed
        if file_path:
            dest_path = os.path.join(os.getcwd(), os.path.basename(file_path))

            # Normalize paths to compare them correctly
            src_normalized = os.path.normpath(file_path)
            dest_normalized = os.path.normpath(dest_path)

            # Check if the source and destination are the same
            if src_normalized == dest_normalized:
                print("Source and destination are the same. Skipping copy.")
            else:
                # Copy the file to the destination
                shutil.copy(file_path, dest_path)

            # Set the flag to indicate the file has been selected

            # Return the full path of the file for further processing
            return dest_path
        else:
            # If the dialog is closed or no file is selected, exit the program
            print('No file selected. Exiting program.')
            sys.exit(0)
     else:
        return file_path  # If the file was already selected, do nothing

# GUI application
def create_gui():
    def on_compress():
        global compress_pressed
        global file_path
        file_path = file_path_sv.get()
        if file_path:
            print(f"File selected and copied: {file_path}")
            result_label.config(text=f"File selected: {file_path}")
            window.destroy()  # Close the window after compression
            compress_pressed = True
        else:
            result_label.config(text="No file selected.")

    def on_choose_file():
        global file_path
        file_path = select_and_copy_file()
        if file_path:
            file_path_sv.set(file_path)
            compress_button.config(state="normal")

    def on_closing():
        print("Exiting program.")
        window.destroy()
        sys.exit(0)

    # Create the main window
    window = tk.Tk()
    window.title("Compression Program")

    # Center the window on the screen
    window_width = 500
    window_height = 100
    screen_width = window.winfo_screenwidth()
    screen_height = window.winfo_screenheight()
    position_top = int(screen_height/2 - window_height/2)
    position_right = int(screen_width/2 - window_width/2)
    window.geometry(f'{window_width}x{window_height}+{position_right}+{position_top}')

    # Handle window close event
    window.protocol("WM_DELETE_WINDOW", on_closing)

    # File path StringVar
    file_path_sv = tk.StringVar()

    # Choose file button
    choose_file_button = tk.Button(window, text="Choose a file", command=on_choose_file)
    choose_file_button.pack(padx=10, pady=10, side=tk.LEFT)

    # File path display
    file_path_display = tk.Entry(window, textvariable=file_path_sv, width=50)
    file_path_display.pack(padx=10, pady=10, side=tk.LEFT)

    # Compress button (initially disabled)
    compress_button = tk.Button(window, text="Compress", command=on_compress, state="disabled")
    compress_button.pack(padx=10, pady=10, side=tk.LEFT)

    # Label to display the result
    result_label = tk.Label(window, text="")
    result_label.pack(pady=10)

    # Start the GUI event loop
    window.mainloop()

# Run the GUI
create_gui()

# Additional code that should run after the window is closed
print("Window closed, continuing with other functions...")
# Call other functions here as needed
