<?php

class open_graph_image {

	public $data = array('og:image:url' => null, 'og:image:secure_url' => null, 'og:image:type' => null, 'og:image:width' => null, 'og:image:height' => null);

	public function __construct($url = null) {
		if( ! empty($url)) $this->data['og:image:url'] = $url;
	}

	public function __toString() {
		// if no url, then no tag.
		if(empty($this->data['og:image:url'])) return '';
		$data = array_filter($this->data); // remove empties
		// if we only have the url, we will simplify the tag
		if(count($data) == 1) $data = array('og:image' => $data['og:image:url']);
		return open_graph::get_tags($data);
	}

	public function set_width($width) { $this->data['og:image:width'] = $width; }
}


/*
The og:image property has some optional structured properties:

og:image:url - Identical to og:image.
og:image:secure_url - An alternate url to use if the webpage requires HTTPS.
og:image:type - A MIME type for this image.
og:image:width - The number of pixels wide.
og:image:height - The number of pixels high.
A full image example:

<meta property="og:image" content="http://example.com/ogp.jpg" />
<meta property="og:image:secure_url" content="https://secure.example.com/ogp.jpg" />
<meta property="og:image:type" content="image/jpeg" />
<meta property="og:image:width" content="400" />
<meta property="og:image:height" content="300" />

*/