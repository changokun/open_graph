<?php

class open_graph_profile {

	profile - Namespace URI: http://ogp.me/ns/profile#

profile:first_name - string - A name normally given to an individual by a parent or self-chosen.
profile:last_name - string - A name inherited from a family or marriage and by which the individual is commonly known.
profile:username - string - A short unique string to identify them.
profile:gender - enum(male, female) - Their gender.
	public $url;
	public $secure_url; // An alternate url to use if the webpage requires HTTPS.
	public $type; // A MIME type for this image.
	public $width; // The number of pixels wide.
	public $height; // The number of pixels high.
	protected $structured_properties = array('secure_url', 'type', 'width', 'height');

	public function __toString() {
		// if no url, then no tag.
		if(empty($this->url)) return '';
		$output_values = array();
		$output_values['og:image'] = $this->url;
		foreach(static::$structured_properties as $property_name) {
			if( ! empty($this->$property_name)) $output_values['og:image:' . $property_name] = $this->$property_name;
		}
		$output = PHP_EOL; // just for neat output.
		foreach($output_values as $key => $value) {
			$output .= '<meta property="'. $key . '" content="' . $value . '" />' . PHP_EOL; // todo make a static function fo rthe opengraph class that will make these.
		}
		return $output;
	}
}