# Requires Python 3.6 or higher due to f-strings

# Import libraries
import platform
from pathlib import Path
from tempfile import TemporaryDirectory
import subprocess

from googletrans import Translator

import pytesseract
from pdf2image import convert_from_path
from PIL import Image


def extract(lan):
    relations_data = ""
    if platform.system() == "Windows":
        # We may need to do some additional downloading and setup...
        # Windows needs a PyTesseract Download
        # https://github.com/UB-Mannheim/tesseract/wiki/Downloading-Tesseract-OCR-Engine

        pytesseract.pytesseract.tesseract_cmd = (
            r"C:\Program Files\Tesseract-OCR\tesseract.exe"
        )

        # Windows also needs poppler_exe
        path_to_poppler_exe = Path(r"C:\Users\ANISH AGARWAL\Downloads\poppler-0.68.0_x86\poppler-0.68.0\bin")

        # Put our output files in a sane place...
        out_directory = Path(r"~").expanduser()
    else:
        out_directory = Path("~").expanduser()

    # Path of the Input pdf
    PDF_file = Path(r"bengali1.pdf")

    # Store all the pages of the PDF in a variable
    image_file_list = []

    text_file = out_directory / Path(r"Desktop/CS/hackathons/BITS-HackYouWay/out_text.txt")
    relations_file = out_directory / Path(r"Desktop/CS/hackathons/BITS-HackYouWay/relations.txt")

    with TemporaryDirectory() as tempdir:
        # Create a temporary directory to hold our temporary images.

        """
        Part #1 : Converting PDF to images
        """

        if platform.system() == "Windows":
            pdf_pages = convert_from_path(
                PDF_file, 500, poppler_path=path_to_poppler_exe
            )
        else:
            pdf_pages = convert_from_path(PDF_file, 500)
        # Read in the PDF file at 500 DPI

        # Iterate through all the pages stored above
        for page_enumeration, page in enumerate(pdf_pages, start=1):
            # enumerate() "counts" the pages for us.

            # Create a file name to store the image
            filename = f"{tempdir}\page_{page_enumeration:03}.jpg"

            # Declaring filename for each page of PDF as JPG
            # For each page, filename will be:
            # PDF page 1 -> page_001.jpg
            # PDF page 2 -> page_002.jpg
            # PDF page 3 -> page_003.jpg
            # ....
            # PDF page n -> page_00n.jpg

            # Save the image of the page in system
            page.save(filename, "JPEG")
            image_file_list.append(filename)

        """
        Part #2 - Recognizing text from the images using OCR
        """

        with open(text_file, "a", encoding="utf-8") as output_file:
            # Open the file in append mode so that
            # All contents of all images are added to the same file

            # Iterate from 1 to total number of pages
            for image_file in image_file_list:
                print("PAGE READING DONE ****")
                # Set filename to recognize text from
                # Again, these files will be:
                # page_1.jpg
                # page_2.jpg
                # ....
                # page_n.jpg

                # Recognize the text as string in image using pytesserct
                text = str(((pytesseract.image_to_string(Image.open(image_file), lang="eng+" + lan))))

                # The recognized text is stored in variable text
                # Any string processing may be applied on text
                # Here, basic formatting has been done:
                # In many PDFs, at line ending, if a word can't
                # be written fully, a 'hyphen' is added.
                # The rest of the word is written in the next line
                # Eg: This is a sample text this word here GeeksF-
                # orGeeks is half on first line, remaining on next.
                # To remove this, we replace every '-\n' to ''.
                text = text.replace("-\n", " ")
                _translator = Translator()
                n = len(text)
                step = 3000
                ans = ""
                for i in range(0, n, step):
                    result = _translator.translate(text[i:min(i + step, n)], dest="en")
                    ans = ans + result.text
                # Finally, write the processed text to the file.
                ans = ans.replace("\n", " ")
                output_file.write(ans)
                arr = ans.split(" ")
                for i in range(0, len(arr), 1000000):
                    proc = subprocess.Popen(['./parse'] + arr[i: min(i + 1000000, len(arr))], stdout=subprocess.PIPE)
                    data = proc.communicate()[0]
                    print(data.decode())
                    relations_data = relations_data + data.decode()

    # At the end of the with .. output_file block
    print(relations_data)
    return relations_data
# the file is closed after writing all the text.
# At the end of the with .. tempdir block, the
# TemporaryDirectory() we're using gets removed!
# End of main function!
