from pathlib import Path
import requests
from a import *


def main():
    filename = Path('metadata.pdf')
    url = 'https://ceochandigarh.gov.in/sites/default/files/polling_files/w0010004.pdf'
    response = requests.get(url)
    filename.write_bytes(response.content)
    extract("hin")



if __name__ == "__main__":
    # We only want to run this if it's directly executed!
    main()
