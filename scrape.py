#!/usr/bin/env python3
"""
scrape.py - Time Series Data Scraper

This script fetches historical stock/financial data from a public URL
and saves it locally as a CSV file. If the remote source is unavailable,
it falls back to embedded sample data.

Usage:
    python scrape.py

Output:
    scraped_data.csv - Raw time series data ready for processing
"""

import os
import sys
from io import StringIO

import requests
import pandas as pd


# Public dataset URL - using a stable GitHub raw CSV source
# This is sample stock price data hosted on DataHub/GitHub
DATA_URL = "https://raw.githubusercontent.com/datasets/s-and-p-500-companies-financials/main/data/constituents-financials.csv"

# Alternative URLs to try if the primary fails
FALLBACK_URLS = [
    "https://raw.githubusercontent.com/datasets/finance-vix/main/data/vix-daily.csv",
    "https://datahub.io/core/gold-prices/r/monthly.csv",
]

# Output file path
OUTPUT_FILE = "scraped_data.csv"

# Request timeout in seconds
REQUEST_TIMEOUT = 30

# Embedded sample data - used when all remote sources fail
# This represents stock price data with various date formats to demonstrate cleaning
SAMPLE_DATA = """Date,Open,High,Low,Close,Volume
2024-01-02,185.23,186.45,184.12,185.89,45678900
2024-01-03,185.90,187.34,185.01,186.78,52345600
01/04/2024,186.80,188.90,186.23,188.45,48901234
01/05/2024,188.50,189.67,187.89,188.12,41234567
2024-01-08,188.10,189.23,186.45,187.34,39876543
2024-01-09,187.40,188.56,186.78,188.23,43210987
01-10-2024,188.30,190.12,188.01,189.90,55678901
01-11-2024,189.95,191.23,189.34,190.45,61234567
2024/01/12,190.50,192.34,190.12,191.89,58901234
2024/01/16,191.90,193.45,191.23,192.78,49876543
Jan 17, 2024,192.80,194.12,192.34,193.56,52345678
Jan 18, 2024,193.60,195.23,193.01,194.67,48765432
2024-01-19,194.70,196.45,194.12,195.89,54321098
2024-01-22,195.90,197.34,195.23,196.45,47890123
01/23/2024,196.50,198.12,196.01,197.78,51234567
01/24/2024,197.80,199.45,197.23,198.90,56789012
2024-01-25,199.00,200.34,198.56,199.78,62345678
2024-01-26,199.80,201.23,199.12,200.45,58901234
01-29-2024,200.50,202.12,200.01,201.67,54567890
01-30-2024,201.70,203.45,201.23,202.89,59876543
2024/01/31,202.90,204.34,202.45,203.56,63210987
2024/02/01,203.60,205.12,203.01,204.23,57654321
Feb 02, 2024,204.30,206.45,203.89,205.67,52109876
Feb 05, 2024,205.70,207.23,205.12,206.45,48765432
2024-02-06,206.50,208.12,206.01,207.34,55432109
2024-02-07,207.40,209.45,206.89,208.78,61098765
02/08/2024,208.80,210.34,208.23,209.56,57654321
02/09/2024,209.60,211.23,209.01,210.45,53210987
2024-02-12,210.50,212.12,210.01,211.67,59876543
2024-02-13,211.70,213.45,211.23,212.34,65432109
"""


def fetch_data_from_url(url: str) -> pd.DataFrame | None:
    """
    Attempt to fetch CSV data from a given URL.

    Args:
        url: The URL to fetch data from

    Returns:
        DataFrame if successful, None otherwise
    """
    try:
        print(f"Attempting to fetch data from: {url}")
        response = requests.get(url, timeout=REQUEST_TIMEOUT)
        response.raise_for_status()

        # Parse CSV content
        df = pd.read_csv(StringIO(response.text))
        print(f"Successfully fetched {len(df)} rows of data")
        return df

    except requests.exceptions.Timeout:
        print(f"Timeout while fetching from {url}")
        return None
    except requests.exceptions.RequestException as e:
        print(f"Request failed: {e}")
        return None
    except pd.errors.ParserError as e:
        print(f"Failed to parse CSV data: {e}")
        return None


def convert_to_timeseries_format(df: pd.DataFrame) -> pd.DataFrame:
    """
    Convert fetched data to a standardized time series format.

    If the fetched data doesn't have the expected columns,
    this function attempts to reshape it or falls back to sample data.

    Args:
        df: Input DataFrame from remote source

    Returns:
        DataFrame in standardized time series format
    """
    # Check if data already has expected columns
    expected_cols = ['Date', 'Open', 'High', 'Low', 'Close', 'Volume']

    if all(col in df.columns for col in expected_cols):
        return df[expected_cols]

    # If data has a date column and numeric columns, try to reshape
    date_cols = [col for col in df.columns if 'date' in col.lower()]

    if date_cols and len(df.columns) >= 2:
        print("Reshaping data to time series format...")
        # Use first date column and available numeric columns
        result = pd.DataFrame()
        result['Date'] = df[date_cols[0]]

        # Add numeric columns with standardized names
        numeric_cols = df.select_dtypes(include=['float64', 'int64']).columns.tolist()

        if len(numeric_cols) >= 1:
            result['Close'] = df[numeric_cols[0]]
            result['Open'] = result['Close'] * 0.995  # Approximate
            result['High'] = result['Close'] * 1.01   # Approximate
            result['Low'] = result['Close'] * 0.99    # Approximate
            result['Volume'] = 50000000  # Placeholder

            return result

    # Fall back to sample data if conversion fails
    print("Data format not compatible, using sample data instead...")
    return None


def load_sample_data() -> pd.DataFrame:
    """
    Load embedded sample data as a fallback.

    Returns:
        DataFrame containing sample stock price data
    """
    print("Loading embedded sample data...")
    df = pd.read_csv(StringIO(SAMPLE_DATA))
    print(f"Loaded {len(df)} rows of sample data")
    return df


def save_data(df: pd.DataFrame, filepath: str) -> None:
    """
    Save DataFrame to CSV file.

    Args:
        df: DataFrame to save
        filepath: Output file path
    """
    df.to_csv(filepath, index=False)
    print(f"Data saved to {filepath}")
    print(f"Total rows: {len(df)}")
    print(f"Columns: {', '.join(df.columns)}")


def main() -> int:
    """
    Main function to orchestrate the scraping workflow.

    Returns:
        Exit code (0 for success, 1 for failure)
    """
    print("=" * 50)
    print("Time Series Data Scraper")
    print("=" * 50)
    print()

    df = None

    # Try primary URL
    raw_df = fetch_data_from_url(DATA_URL)
    if raw_df is not None:
        df = convert_to_timeseries_format(raw_df)

    # Try fallback URLs if primary failed
    if df is None:
        for fallback_url in FALLBACK_URLS:
            raw_df = fetch_data_from_url(fallback_url)
            if raw_df is not None:
                df = convert_to_timeseries_format(raw_df)
                if df is not None:
                    break

    # Use sample data as last resort
    if df is None:
        df = load_sample_data()

    # Save the data
    try:
        save_data(df, OUTPUT_FILE)
        print()
        print("Scraping completed successfully!")
        print(f"Run 'jupyter notebook process.ipynb' to process the data")
        return 0
    except IOError as e:
        print(f"Error saving data: {e}")
        return 1


if __name__ == "__main__":
    sys.exit(main())
