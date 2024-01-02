DROP DATABASE IF EXISTS arduino_db;
CREATE DATABASE arduino_db;
USE arduino_db;

CREATE TABLE dataset (
	id_ds int NOT NULL AUTO_INCREMENT,
    name_room_ds VARCHAR(100) NULL,
    status_ds boolean DEFAULT FALSE,
    created_at_ds TIMESTAMP DEFAULT current_timestamp,
    weekday_ds VARCHAR(20) NULL,
    month_ds VARCHAR(30) NULL,
    PRIMARY KEY(id_ds)
);

DELIMITER //
CREATE TRIGGER before_insert_dataset
BEFORE INSERT ON dataset
FOR EACH ROW
BEGIN
    SET NEW.weekday_ds = DAYNAME(NOW());
    SET NEW.month_ds = MONTHNAME(NOW());
END;
//
DELIMITER ;

-- Inserção de dados na tabela dataset
SELECT * FROM dataset;