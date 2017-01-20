# !bin/bash
USER="root"
PWD="123456"
DATABASE="test_db"
mysql $DATABASE < ./data-script/create_table.sql
