-- phpMyAdmin SQL Dump
-- version 3.5.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jun 02, 2014 at 12:11 PM
-- Server version: 5.5.24-log
-- PHP Version: 5.3.13

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

DROP DATABASE els;

CREATE DATABASE els;

USE els;

--
-- Database: `els`
--

--
-- Table structure for table `accounts`
--

CREATE TABLE IF NOT EXISTS `accounts` (
  `id` int(10) unsigned NOT NULL,
  `name` varchar(45) NOT NULL,
  `password` varchar(255) NOT NULL,
  `salt` varchar(45) NOT NULL,
  `email` varchar(255) NOT NULL,
  `status` smallint(5) unsigned NOT NULL DEFAULT '0',
  `migration_serial` varchar(45) NOT NULL,
  `last_login` datetime NOT NULL,
  `banned` tinyint(1) NOT NULL DEFAULT '0',
  `ip` varchar(45) NOT NULL,
  `creation_date` datetime NOT NULL,
  `charslots` int(10) unsigned NOT NULL DEFAULT '7',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Table structure for table `characters`
--

CREATE TABLE IF NOT EXISTS `characters` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `accid` int(10) unsigned NOT NULL,
  `name` varchar(45) NOT NULL,
  `level` int(10) unsigned NOT NULL DEFAULT '1',
  `exp` int(10) unsigned NOT NULL DEFAULT '0',
  `hp` int(10) unsigned NOT NULL,
  `attack` int(10) unsigned NOT NULL,
  `mattack` int(10) unsigned NOT NULL,
  `def` int(10) unsigned NOT NULL,
  `mdef` int(10) unsigned NOT NULL,
  `ed` int(10) unsigned NOT NULL,
  `unittype` smallint(5) unsigned NOT NULL,
  `unitclass` smallint(5) unsigned NOT NULL,
  `createdate` datetime NOT NULL,
  `map` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Table structure for table `equip`
--

CREATE TABLE IF NOT EXISTS `equip` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `itemid` int(10) unsigned NOT NULL,
  `endurance` int(10) unsigned NOT NULL DEFAULT '0',
  `decorative` tinyint(1) NOT NULL,
  `equipped` tinyint(1) NOT NULL,
  `isequip` tinyint(1) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `item`
--

CREATE TABLE IF NOT EXISTS `item` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `charid` int(10) unsigned NOT NULL,
  `itemid` int(10) unsigned NOT NULL,
  `quantity` int(10) unsigned NOT NULL,
  `expiredate` datetime NOT NULL,
  `isequip` tinyint(1) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `kom_item`
--

CREATE TABLE IF NOT EXISTS `kom_item` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `itemid` int(11) NOT NULL,
  `name` text,
  `usetype` int(11) DEFAULT NULL,
  `usecondition` int(11) DEFAULT NULL,
  `unittype` int(11) DEFAULT NULL,
  `unitclass` int(11) DEFAULT NULL,
  `uselevel` int(11) DEFAULT NULL,
  `itemlevel` int(11) DEFAULT NULL,
  `itemtype` int(11) DEFAULT NULL,
  `itemgrade` int(11) DEFAULT NULL,
  `endurance` int(11) DEFAULT NULL,
  `equippos` int(11) DEFAULT NULL,
  `basehp` int(11) DEFAULT NULL,
  `atkphysic` int(11) DEFAULT NULL,
  `atkmagic` int(11) DEFAULT NULL,
  `defphysic` int(11) DEFAULT NULL,
  `defmagic` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;
