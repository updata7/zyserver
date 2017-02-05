# !bin/bash
mysql -h 127.0.0.1 -P 3308 -uroot -p123456 --database test_db < ./data-script/create_table.sql