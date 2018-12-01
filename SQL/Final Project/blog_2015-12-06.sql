# ************************************************************
# Sequel Pro SQL dump
# Version 4499
#
# http://www.sequelpro.com/
# https://github.com/sequelpro/sequelpro
#
# Host: localhost (MySQL 5.5.38)
# Database: blog
# Generation Time: 2015-12-07 00:54:43 +0000
# ************************************************************


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


# Dump of table comments
# ------------------------------------------------------------

DROP TABLE IF EXISTS `comments`;

CREATE TABLE `comments` (
  `comment_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `c_username` varchar(30) DEFAULT NULL,
  `body` varchar(5000) DEFAULT NULL,
  `post_id` int(10) DEFAULT NULL,
  `dateTime` datetime DEFAULT NULL,
  PRIMARY KEY (`comment_id`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=latin1;

LOCK TABLES `comments` WRITE;
/*!40000 ALTER TABLE `comments` DISABLE KEYS */;

INSERT INTO `comments` (`comment_id`, `c_username`, `body`, `post_id`, `dateTime`)
VALUES
	(1,'Dr. Kevorkian','Andy nobody cares....',1,'2010-03-15 00:00:00'),
	(2,'Dr. Kevorkian','Me Hoy Minoy!',6,'2015-05-27 00:00:00'),
	(3,'MaidOfOrleans','Well thats just awful, ill do something about that. ',8,'1862-08-19 00:00:00'),
	(4,'GsaveTheQueen','You sir are the worst monarch ive ever seen. I am not amused.',4,'1977-01-10 00:00:00'),
	(5,'EmperorSidious','Im rooting for Javert! You criminal. ',8,'1862-08-19 00:00:00'),
	(6,'CommonSense','Where?',7,'1779-10-14 00:00:00'),
	(7,'LibertyOrDeath','On the back, you just cant see it.',7,'1779-10-14 00:00:00'),
	(8,'CommonSense','You\'re lying Franklin. ',7,'1779-10-14 00:00:00'),
	(9,'LibertyOrDeath',' They made a movie about it...National Treasure...',7,'1779-10-14 00:00:00'),
	(10,'CommonSense','Thats fiction Franklin...',7,'1779-10-14 00:00:00'),
	(11,'AndyBoy27','Where do I sign up? I <3 cookies. ',5,'2015-03-18 00:00:00'),
	(12,'EmperorSidious','The nearest imperal outpost. ',5,'2015-03-18 00:00:00'),
	(13,'EmperorSidious','Btw the cookies are Oreos.',5,'2015-03-18 00:00:00'),
	(14,'jamesKnightPolk','No dont do it Andy!',5,'2015-03-19 00:00:00'),
	(15,'MonsieurLaMayor','So do I!',2,'2014-09-08 00:00:00');

/*!40000 ALTER TABLE `comments` ENABLE KEYS */;
UNLOCK TABLES;


# Dump of table posts
# ------------------------------------------------------------

DROP TABLE IF EXISTS `posts`;

CREATE TABLE `posts` (
  `post_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `title` varchar(255) DEFAULT NULL,
  `body` varchar(5000) DEFAULT NULL,
  `username` varchar(30) DEFAULT NULL,
  `dateTime` datetime DEFAULT NULL,
  PRIMARY KEY (`post_id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=latin1;

LOCK TABLES `posts` WRITE;
/*!40000 ALTER TABLE `posts` DISABLE KEYS */;

INSERT INTO `posts` (`post_id`, `title`, `body`, `username`, `dateTime`)
VALUES
	(1,'My First Post','Guys look at my first blog post!','AndyBoy27','2010-03-14 00:00:00'),
	(2,'I Love Eggnog','I\'ve been drinking way too much eggnog.','Dr. Kevorkian','2013-12-01 00:00:00'),
	(3,'God Save the Queen','Who doesnt love us Britich Monarchy am I right?','GsaveTheQueen','1850-06-05 00:00:00'),
	(4,'Damn the Rebel Scum!','5 mill Imperial Credits to anyone who catches Leia Organa. ','EmperorSidious','1977-01-08 00:00:00'),
	(5,'We Have Cookies','Come to the Dark Side. ','EmperorSidious','1978-01-03 00:00:00'),
	(6,'Loram ipsum','Dolor sit amet, consectetur dipiscing elit. ','jamesKnightPolk','2015-05-27 00:00:00'),
	(7,'Many peeps dont know...','But there is a treasure map on the back of the Declaration of Independance. ','LibertyOrDeath','1778-11-11 00:00:00'),
	(8,'France\'s penal system is just awful','I served 20 years for stealing some bread!','MonsieurLaMayor','1862-08-15 00:00:00');

/*!40000 ALTER TABLE `posts` ENABLE KEYS */;
UNLOCK TABLES;


# Dump of table users
# ------------------------------------------------------------

DROP TABLE IF EXISTS `users`;

CREATE TABLE `users` (
  `username` varchar(30) NOT NULL DEFAULT '',
  `password` varchar(40) CHARACTER SET latin1 COLLATE latin1_bin DEFAULT NULL,
  `email` varchar(30) DEFAULT NULL,
  `name` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;

INSERT INTO `users` (`username`, `password`, `email`, `name`)
VALUES
	('AndyBoy27',X'797472657771','AndyH@yahoo.com','Andy Huang'),
	('CommonSense',X'547061696E65313233','Tpaine@google.com','Thomas Paine'),
	('Dr. Kevorkian',X'3132333435','patrickkevorkian@gmail.com','Patrick Kevorkian'),
	('EmperorSidious',X'536B7977616C6B657248386572','Emperor@Deathstar.gov','Sheev Palpatine'),
	('GsaveTheQueen',X'666872747573473536','Qvictoria@parliment.gov','Alexandria Victoria'),
	('jamesKnightPolk',X'717765727479','steven@hotmail.com','Steven Wojcik'),
	('LibertyOrDeath',X'31373736555341','BenFranks@whitehouse.gov','Benjamin Franklin'),
	('MaidOfOrleans',X'764875676F333435','JoanOArc@Aol.com','Jeanne d\'Arc'),
	('MonsieurLaMayor',X'3234363031','BreadforSister@yahoo.com','Jean Valjean');

/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;



/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
