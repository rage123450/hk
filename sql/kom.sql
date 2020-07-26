DROP DATABASE IF EXISTS els;

CREATE DATABASE els;

USE els;

CREATE TABLE `kom_item` (
	`id` INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
	`itemid` INT NOT NULL,
	`name` TEXT,
	`usetype` INT,
	`usecondition` INT,
	`unittype` INT,
	`unitclass` INT,
	`uselevel` INT,
	`itemlevel` INT,
	`itemtype` INT,
	`itemgrade` INT,
	`endurance` INT,
	`equippos` INT,
	`basehp` INT,
	`atkphysic` INT,
	`atkmagic` INT,
	`defphysic` INT,
	`defmagic` INT
);
	