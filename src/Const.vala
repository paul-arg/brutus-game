public const int TILE_WIDTH = 45; //32
public const int TILE_HEIGHT = 26; //18
public const int OFFSET_X = 192;
public const int OFFSET_Y = 0;

public const string custom_css = 
"""*{
		outline:none;
	}
	.panel button,
	.panel .button {
		margin:1px;
		color: white;
		border-color: brown;
		border-style: outset;
		background-image: -gtk-gradient(radial, center center , 0, center center, 1, from(rgb(196, 36, 36)), to(rgb(106, 19, 19))); 
		border-width: 3px;
		border-radius: 6px;
		box-shadow:0 2px 3px -2px black;
		transition: 100ms background ease;
	}
	.panel .button:active {
		background-image: -gtk-gradient(radial, center center , 0, center center, 1, from(rgb(106, 19, 19)), to(rgb(156, 36, 36))); 
		border-color: #391818;
		border-style: inset;
		box-shadow:0 0 3px alpha(black,0.4);
	}
	.panel .button:checked {
		background-image: -gtk-gradient(radial, center center , 0, center center, 1, from(rgb(106, 19, 19)), to(rgb(156, 36, 36))); 
		border-color: #5F0808;
		border-style: inset;
		box-shadow:0 0 3px alpha(black,0.4);
	}
	.panel button.text-button {
		background-color: transparent;
		border:none;
	}
	.panel .label {
		background-color:transparent;
		border:none;
	}
	.panel {
		background-image: -gtk-gradient(radial, center center , 0, center center, 1, from(rgb(209, 111, 81)), to(rgb(116, 52, 33))); 
		border: 3px outset rgb(50, 19, 18);
	}
	.panel .button{
		color: rgba(250, 130, 80,.7);
			icon-shadow: 1px  1px alpha(black,.6), -1px  -1px alpha(white,.8);
			text-shadow: 1px  1px alpha(black,.6), -1px  -1px alpha(white,.8);
	}
	.panel .button:active{
		color: alpha(black,.5);
			icon-shadow: -1px  -1px alpha(black,.4), 1px  1px alpha(white,.2);
			text-shadow: -1px  -1px alpha(black,.4), 1px  1px alpha(white,.2);
	}""";
