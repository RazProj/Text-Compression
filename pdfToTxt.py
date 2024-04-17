import PyPDF2
import importFile

pdf_path = importFile.select_and_copy_file()
output_path = 'extracted_text.txt'
def extract_and_save_text(pdf_path, output_path):
    pdf_file = open(pdf_path, 'rb')
    pdf_reader = PyPDF2.PdfReader(pdf_file)
    output_file = open(output_path, 'w')

    for page_num in range(len(pdf_reader.pages)):
        text = pdf_reader.pages[page_num].extract_text()
        for char in text:
            if 32 <= ord(char) <= 128:
                output_file.write(char)
    output_file.close()
    pdf_file.close()

extract_and_save_text(pdf_path, output_path)
