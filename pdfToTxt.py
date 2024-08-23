import PyPDF2
import importFile

def extract_and_save_text(pdf_path, output_path):
    try:
        pdf_file = open(pdf_path, 'rb')
        print(pdf_file)
        pdf_reader = PyPDF2.PdfReader(pdf_file)
        output_file = open(output_path, 'w')

        for page_num in range(len(pdf_reader.pages)):
            text = pdf_reader.pages[page_num].extract_text()
            for char in text:
                if 32 <= ord(char) <= 128:
                    output_file.write(char)
        output_file.close()
        pdf_file.close()
        print(f"Text successfully extracted to {output_path}")

    except Exception as e:
        print(f"Failed to extract text: {e}")

# Ensure this function call is executed
input_p = importFile.select_and_copy_file()
output_p = 'extracted_text.txt'
extract_and_save_text(input_p, output_p)  # This is the line to check
