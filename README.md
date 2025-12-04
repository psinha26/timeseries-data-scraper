# Time Series Data Scraper

A Python project demonstrating web scraping, data cleaning, merging, and time-series visualization workflows.

## Overview

This project fetches historical stock price data from a public source, processes and cleans the data, generates time-series visualizations, and exports cleaned datasets for further analysis.

## Project Structure

```
timeseries-data-scraper/
├── README.md              # Project documentation
├── requirements.txt       # Python dependencies
├── scrape.py             # Data scraping script
├── process.ipynb         # Data processing notebook
├── scraped_data.csv      # Sample/scraped raw data
└── cleaned_timeseries.csv # Processed output (generated)
```

## Workflow

### 1. Data Scraping (`scrape.py`)

The scraping script fetches time-series data from a public URL:

- **Source**: GitHub raw CSV files or DataHub public datasets
- **Method**: Uses `requests` library to fetch CSV data
- **Output**: Saves raw data to `scraped_data.csv`
- **Fallback**: Uses embedded sample data if network request fails

```bash
python scrape.py
```

### 2. Data Processing (`process.ipynb`)

The Jupyter notebook performs the following operations:

1. **Load Data**: Reads the scraped CSV file into a pandas DataFrame
2. **Clean Date Formats**: Parses and standardizes date columns to datetime format
3. **Handle Missing Values**: Fills or drops missing data points
4. **Data Validation**: Ensures numeric columns are properly typed
5. **Time-Series Visualization**: Creates line charts showing trends over time
6. **Export**: Saves cleaned data to `cleaned_timeseries.csv`

## Installation

### Prerequisites

- Python 3.8 or higher
- pip package manager

### Setup

1. Clone the repository:
```bash
git clone https://github.com/yourusername/timeseries-data-scraper.git
cd timeseries-data-scraper
```

2. Create a virtual environment (recommended):
```bash
python -m venv venv
source venv/bin/activate  # On Windows: venv\Scripts\activate
```

3. Install dependencies:
```bash
pip install -r requirements.txt
```

## Usage

### Step 1: Scrape Data

Run the scraping script to fetch fresh data:

```bash
python scrape.py
```

This will:
- Attempt to download data from the configured URL
- Fall back to sample data if the request fails
- Save the data to `scraped_data.csv`

### Step 2: Process Data

Open and run the Jupyter notebook:

```bash
jupyter notebook process.ipynb
```

Or run all cells programmatically:

```bash
jupyter nbconvert --to notebook --execute process.ipynb
```

### Output Files

After running both scripts:

- `scraped_data.csv`: Raw data from the source
- `cleaned_timeseries.csv`: Processed and cleaned time-series data

## Data Schema

### Input Data (`scraped_data.csv`)

| Column | Type   | Description                    |
|--------|--------|--------------------------------|
| Date   | string | Date in various formats        |
| Open   | float  | Opening price                  |
| High   | float  | Highest price of the day       |
| Low    | float  | Lowest price of the day        |
| Close  | float  | Closing price                  |
| Volume | int    | Trading volume                 |

### Output Data (`cleaned_timeseries.csv`)

| Column | Type     | Description                    |
|--------|----------|--------------------------------|
| Date   | datetime | Standardized ISO date format   |
| Open   | float    | Opening price (cleaned)        |
| High   | float    | Highest price (cleaned)        |
| Low    | float    | Lowest price (cleaned)         |
| Close  | float    | Closing price (cleaned)        |
| Volume | int      | Trading volume (cleaned)       |

## Dependencies

- **pandas**: Data manipulation and analysis
- **requests**: HTTP library for fetching data
- **matplotlib**: Plotting and visualization
- **jupyter**: Interactive notebook environment

See `requirements.txt` for version details.

## Sample Data

The repository includes sample stock price data (`scraped_data.csv`) that can be used when:
- The remote data source is unavailable
- Testing the processing pipeline
- Running offline demonstrations

## Troubleshooting

### Network Issues

If the scraping script fails to fetch data:
1. Check your internet connection
2. Verify the source URL is accessible
3. The script will automatically use sample data as fallback

### Date Parsing Errors

If date parsing fails in the notebook:
1. Check the date format in your source data
2. Modify the `pd.to_datetime()` format parameter as needed

### Missing Dependencies

If you encounter import errors:
```bash
pip install -r requirements.txt --upgrade
```

## License

MIT License - feel free to use and modify for your projects.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request
