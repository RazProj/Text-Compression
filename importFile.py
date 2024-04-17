import tkinter as tk
from tkinter import filedialog
import shutil
import os
import sys

def select_and_copy_file():

    root = tk.Tk()
    root.withdraw()

    # Prompt the user to select a PDF file
    file_path = filedialog.askopenfilename(filetypes=[("PDF files", "*.pdf")])

    # Check if a file was selected
    if file_path:

        dest_path = os.path.join(os.getcwd(), os.path.basename(file_path))

        # Copy the file to the destination
        shutil.copy(file_path, dest_path)
        # Return the name of the file for further processing
        return os.path.basename(file_path)
    else:
        print('No file selected.')
        sys.exit(1)
