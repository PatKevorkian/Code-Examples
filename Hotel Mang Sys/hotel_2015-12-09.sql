# ************************************************************
# Sequel Pro SQL dump
# Version 4499
#
# http://www.sequelpro.com/
# https://github.com/sequelpro/sequelpro
#
# Host: localhost (MySQL 5.5.38)
# Database: hotel
# Generation Time: 2015-12-09 16:42:46 +0000
# ************************************************************


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


# Dump of table employees
# ------------------------------------------------------------

DROP TABLE IF EXISTS `employees`;

CREATE TABLE `employees` (
  `name` varchar(30) NOT NULL DEFAULT '',
  `user_name` varbinary(30) NOT NULL DEFAULT '',
  `password` varbinary(30) NOT NULL DEFAULT '',
  `emp_type` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

LOCK TABLES `employees` WRITE;
/*!40000 ALTER TABLE `employees` DISABLE KEYS */;

INSERT INTO `employees` (`name`, `user_name`, `password`, `emp_type`)
VALUES
	('Patrick Kevorkian',X'706174',X'31',1),
	('Andy Haung ',X'616E6479',X'32',0);

/*!40000 ALTER TABLE `employees` ENABLE KEYS */;
UNLOCK TABLES;


# Dump of table menu
# ------------------------------------------------------------

DROP TABLE IF EXISTS `menu`;

CREATE TABLE `menu` (
  `item_name` varchar(30) NOT NULL DEFAULT '',
  `price` decimal(6,2) unsigned NOT NULL,
  `description` varchar(96) NOT NULL DEFAULT ''
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

LOCK TABLES `menu` WRITE;
/*!40000 ALTER TABLE `menu` DISABLE KEYS */;

INSERT INTO `menu` (`item_name`, `price`, `description`)
VALUES
	('Steak',15.00,'A prime cut of beef tenderloin served to order.'),
	('Chicken parm',12.00,'Fried chicken with sauce and cheese. '),
	('French Fries',4.00,'Fried potatoes.'),
	('Champagne ',100.00,'a bottle '),
	('Coke',2.00,'A bottle of carbinated water with syrup');

/*!40000 ALTER TABLE `menu` ENABLE KEYS */;
UNLOCK TABLES;


# Dump of table order_items
# ------------------------------------------------------------

DROP TABLE IF EXISTS `order_items`;

CREATE TABLE `order_items` (
  `order_num` int(13) unsigned NOT NULL,
  `item` varchar(30) NOT NULL DEFAULT ''
) ENGINE=InnoDB DEFAULT CHARSET=latin1;



# Dump of table orders
# ------------------------------------------------------------

DROP TABLE IF EXISTS `orders`;

CREATE TABLE `orders` (
  `order_num` int(13) unsigned NOT NULL AUTO_INCREMENT,
  `room_num` varchar(11) NOT NULL,
  `record_num` int(13) unsigned NOT NULL,
  `finished` tinyint(1) unsigned NOT NULL,
  PRIMARY KEY (`order_num`)
) ENGINE=InnoDB AUTO_INCREMENT=35 DEFAULT CHARSET=latin1;

LOCK TABLES `orders` WRITE;
/*!40000 ALTER TABLE `orders` DISABLE KEYS */;

INSERT INTO `orders` (`order_num`, `room_num`, `record_num`, `finished`)
VALUES
	(1,'1',1,1),
	(13,'1',1,1),
	(14,'1',1,1),
	(15,'1',1,1),
	(16,'1',1,1),
	(17,'1',1,1),
	(18,'1',1,1),
	(19,'2',6,1),
	(20,'3',4,1),
	(21,'2',6,1),
	(22,'1',1,1),
	(23,'3',7,1),
	(24,'2',8,1),
	(25,'1',9,1),
	(28,'1',9,1),
	(29,'2',10,1),
	(31,'1',12,1),
	(33,'3',11,1),
	(34,'2',14,0);

/*!40000 ALTER TABLE `orders` ENABLE KEYS */;
UNLOCK TABLES;


# Dump of table records
# ------------------------------------------------------------

DROP TABLE IF EXISTS `records`;

CREATE TABLE `records` (
  `record_num` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(30) NOT NULL DEFAULT '',
  `cc_num` varchar(19) NOT NULL DEFAULT '',
  `exp_date` varchar(7) NOT NULL DEFAULT '',
  `room_num` varchar(4) NOT NULL DEFAULT '',
  `time_in` date NOT NULL DEFAULT '0000-00-00',
  `time_out` date NOT NULL DEFAULT '0000-00-00',
  `price` decimal(7,2) NOT NULL DEFAULT '0.00',
  PRIMARY KEY (`record_num`)
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=latin1;

LOCK TABLES `records` WRITE;
/*!40000 ALTER TABLE `records` DISABLE KEYS */;

INSERT INTO `records` (`record_num`, `name`, `cc_num`, `exp_date`, `room_num`, `time_in`, `time_out`, `price`)
VALUES
	(1,'Steven James','6666-6666-6666-6666','66/6666','1','2015-04-30','2015-05-02',924.00),
	(4,'Patrick Star','1111-1111-1111-1111','11/1111','3','2015-04-30','2015-05-02',215.00),
	(6,'steve','4444-4444-4444-4444','04/2016','2','2015-05-01','2015-05-02',147.00),
	(7,'Steven K','1231-2312-3123-1231','09/2018','3','2015-05-02','2015-05-02',749.00),
	(8,'abc easyas','1231-2312-3111-2311','12/2018','2','2015-05-02','2015-05-02',0.00),
	(9,'First Name','0987-6543-2456-7892','12/2015','1','2015-05-02','2015-05-02',116.00),
	(10,'Patty Watty','1231-2321-3123-1231','08/2018','2','2015-05-02','2015-05-02',111.00),
	(11,'Georgie Foreman','1231-1233-3123-1231','01/2017','3','2015-05-02','0000-00-00',105.00),
	(12,'Chuck Norris','6666-6666-6666-6666','08/2017','1','2015-05-02','2015-05-02',54.00),
	(13,'Chuck Borris','1111-1111-1111-1111','11/2018','2','2015-05-02','2015-05-02',0.00),
	(14,'DoYouSee MyName','1231-2312-1231-2312','09/2017','2','2015-05-02','0000-00-00',0.00);

/*!40000 ALTER TABLE `records` ENABLE KEYS */;
UNLOCK TABLES;


# Dump of table rooms
# ------------------------------------------------------------

DROP TABLE IF EXISTS `rooms`;

CREATE TABLE `rooms` (
  `room_num` varchar(4) NOT NULL DEFAULT '',
  `beds` varchar(1) NOT NULL DEFAULT '',
  `baths` varchar(1) NOT NULL DEFAULT '',
  `balcony` tinyint(1) NOT NULL,
  `oceanv` tinyint(1) NOT NULL,
  `suite` tinyint(1) NOT NULL,
  `ppn` decimal(7,2) NOT NULL,
  `vacant` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`room_num`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

LOCK TABLES `rooms` WRITE;
/*!40000 ALTER TABLE `rooms` DISABLE KEYS */;

INSERT INTO `rooms` (`room_num`, `beds`, `baths`, `balcony`, `oceanv`, `suite`, `ppn`, `vacant`)
VALUES
	('1','2','1',0,0,0,50.00,1),
	('2','1','1',1,0,0,30.00,0),
	('3','3','2',1,1,1,100.00,0),
	('4','1','1',1,1,0,40.00,1);

/*!40000 ALTER TABLE `rooms` ENABLE KEYS */;
UNLOCK TABLES;



/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
