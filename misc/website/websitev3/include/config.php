<?php
$LATEST_PH_VERSION = "2.33";
$LATEST_PH_BUILD = "5590";
$LATEST_PH_RELEASE_DATE = "27th of December 2013";

$LATEST_PH_BIN_SIZE = "2.7 MB";
$LATEST_PH_BIN_SHA1 = "2738c909fa6b37a22a4aa256e5d7e733449b905e";

$LATEST_PH_SDK_SIZE = "2.7 MB";
$LATEST_PH_SDK_SHA1 = "5b17c8c555298cc10ea297f1ce7977ea50f09d9d";

$LATEST_PH_SETUP_SIZE = "1.9 MB";
$LATEST_PH_SETUP_SHA1 = "f328286bdf529e3905e8098b8d7558f974d9293c";

$LATEST_PH_SOURCE_SIZE = "2.6 MB";
$LATEST_PH_SOURCE_SHA1 = "9f8d97d5409e5f4e49cbd7dd8e12df29d17658ff";

$LATEST_PH_RELEASE_NEWS = "http://processhacker.sourceforge.net/forums/viewtopic.php?f=1&t=1294";
$LATEST_PH_RELEASE_URL = "http://sourceforge.net/projects/processhacker/files/processhacker2/processhacker-".$LATEST_PH_VERSION."-setup.exe/download?use_mirror=autoselect";

// =================================================
// Setup database details
@include('../forums/config.php');

$topicnumber = 5;
$table_topics = @$table_prefix. "topics";
$table_forums = @$table_prefix. "forums";
$table_posts = @$table_prefix. "posts";
$table_users = @$table_prefix. "users";
$table_sessions = @$table_prefix. "sessions";
$table_plugins = @$table_prefix. "plugins";

// function for converting time into time elapsed
function get_time_ago($time_stamp)
{
    $time_difference = strtotime('now') - $time_stamp;

    if ($time_difference >= 60 * 60 * 24 * 365.242199) 
    {
        /*
         * 60 seconds/minute * 60 minutes/hour * 24 hours/day * 365.242199 days/year
         * This means that the time difference is 1 year or more
         */
        return get_time_ago_string($time_stamp, 60 * 60 * 24 * 365.242199, 'year');
    } 
    elseif ($time_difference >= 60 * 60 * 24 * 30.4368499) 
    {
        /*
         * 60 seconds/minute * 60 minutes/hour * 24 hours/day * 30.4368499 days/month
         * This means that the time difference is 1 month or more
         */
        return get_time_ago_string($time_stamp, 60 * 60 * 24 * 30.4368499, 'month');
    } 
    elseif ($time_difference >= 60 * 60 * 24 * 7) 
    {
        /*
         * 60 seconds/minute * 60 minutes/hour * 24 hours/day * 7 days/week
         * This means that the time difference is 1 week or more
         */
        return get_time_ago_string($time_stamp, 60 * 60 * 24 * 7, 'week');
    } 
    elseif ($time_difference >= 60 * 60 * 24) 
    {
        /*
         * 60 seconds/minute * 60 minutes/hour * 24 hours/day
         * This means that the time difference is 1 day or more
         */
        return get_time_ago_string($time_stamp, 60 * 60 * 24, 'day');
    } 
    elseif ($time_difference >= 60 * 60) 
    {
        /*
         * 60 seconds/minute * 60 minutes/hour
         * This means that the time difference is 1 hour or more
         */
        return get_time_ago_string($time_stamp, 60 * 60, 'hour');
    } 
    else 
    {
        /*
         * 60 seconds/minute
         * This means that the time difference is a matter of minutes
         */
        return get_time_ago_string($time_stamp, 60, 'minute');
    }
}

function get_time_ago_string($time_stamp, $divisor, $time_unit)
{
    $time_difference = strtotime("now") - $time_stamp;
    $time_units      = floor($time_difference / $divisor);

    settype($time_units, 'string');

    if ($time_units === '0') {
        return 'less than 1 ' . $time_unit . ' ago';
    } elseif ($time_units === '1') {
        return '1 ' . $time_unit . ' ago';
    } else {
        /*
         * More than "1" $time_unit. This is the "plural" message.
         */
        // TODO: This pluralizes the time unit, which is done by adding "s" at the end; this will not work for i18n!
        return $time_units . ' ' . $time_unit . 's ago';
    }
}

// This function summarizes posts to max. 1200 characters
function summary($str, $limit = 1200, $strip = false) {
    $str = ($strip == true) ? strip_tags($str) : $str;
    if (strlen ($str) > $limit) {
        $str = substr ($str, 0, $limit - 3);
        return trim(substr ($str, 0, strrpos ($str, ' ')).'...');
    }
    return trim($str);
}
?>
