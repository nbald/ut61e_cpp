~es51922~

compile:
    - cd in this directory
    - make

usage:

    - interpret stored raw data from the es51922 serial port and store into another file:
        cat raw_log_data.file | ./es51922 > well_formatted_spreadsheedfriendly.csv

      [!] note that the timestamps will be nonsense if you use a stored raw log
          because they are generated during conversion and not during capture.

    - use direct data source (-> usb interface cable) and show on screen:
        ./he2325u | ./es51922
