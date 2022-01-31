var cc1 = {
	type: 'doughnut',
	data: {
		datasets: [{
			data: [100,100, 100],
			backgroundColor: [
				'rgb(93, 201, 105)',
				'rgb(90, 209, 209)',
				'rgb(237, 148, 69)',
			],
		}],
		labels: [
			'Floor1',
			'Floor2',
			'Floor3'
		],
	},
	options: {
		
		responsive: true,
		circumference: Math.PI* 2.0,
		title: {
			display: true,
		},
	}
};

var cc2 = {
	type: 'line',
	data: {
		labels:[1,2,3, 4, 5, 6, 7, 8, 9, 10],
		datasets: [{
			label: 'Elevator',
			fill: false,
			data: [1, 2, 3, 3, 2, 1, 2, 3,1,1],
			backgroundColor: window.chartColors.purple,
			borderColor: window.chartColors.purple,
		},]
	},	
	options: {
			responsive: true,
			title: {
				display: true
			},
			legend: {
				position: 'top',
			},
			scales: {
				xAxes: [{
					display: true,
					scaleLabel: {
						display: true,
						labelString: 'Request Time'
					},
					ticks: {
						beginAtZero: true,
						min: 0,
						max: 10,
						stepSize: 1
					}
				}],
				yAxes: [{
					display: true,
					ticks: {
						beginAtZero: false, 	
						min: 1,
						max: 4,
						stepSize: 1
					},
					scaleLabel: {
						display: true,
						labelString: 'Floor Number',
					}
				}],
			}
		}
};

var cc3 = {
	type: 'line',
	data: {
		labels:[1,2,3, 4, 5, 6, 7, 8, 9, 10],
		datasets: [{
			label: 'Elevator',
			fill: false,
			data: [1, 2, 3, 2, 1, 2, 3, 2,1,2],
			backgroundColor: window.chartColors.purple,
			borderColor: window.chartColors.purple,
		},]
	},	
	options: {
			responsive: true,
			title: {
				display: true
			},
			legend: {
				position: 'top',
			},
			scales: {
				xAxes: [{
					display: true,
					scaleLabel: {
						display: true,
						labelString: 'Request Number'
					},
					ticks: {
						beginAtZero: true,
						min: 0,
						max: 10,
						stepSize: 1
					}
				}],
				yAxes: [{
					display: true,
					ticks: {
						beginAtZero: false,
						min: 1,
						max: 4,
						stepSize: 1
					},
					scaleLabel: {
						display: true,
						labelString: 'Floor Number',
					}
				}],
			}
		}
};

var cc4 = {
	type: 'doughnut',
	data: {
		datasets: [{
			data: [100,100, 100],
			backgroundColor: [
				'rgb(93, 201, 105)',
				'rgb(90, 209, 209)',
				'rgb(237, 148, 69)',
			],
		}],
		labels: [
			'Floor 1',
			'Floor 2',
			'Floor 3'
		],
	},
	options: {
		responsive: true,
		circumference: Math.PI* 2.0,
		title: {
			display: true,
		},
	}
};

window.addEventListener("load",function(){
	updateChart();
});

function updateChart(){
		var ctx1;	
		var ctx2;
		var ctx3;
		var ctx4;
		ctx1 = document.getElementById('floorReqCanvas').getContext('2d');
		window.FloorCount = new Chart(ctx1, cc1);
		window.FloorCount.options.title.text = "Floor access count";
		
		ctx2 = document.getElementById('lastHourCanvas').getContext('2d');
		window.lastHour = new Chart(ctx2, cc2);
		window.lastHour.options.title.text = "Requests in the last hour";
		
		ctx3 = document.getElementById('lastTenCanvas').getContext('2d');
		window.last10 = new Chart(ctx3, cc3);
		window.last10.options.title.text = "Last 10 Requests";
		
		ctx4 = document.getElementById('callsByFloor').getContext('2d');
		window.callsByFloor = new Chart(ctx4, cc4);
		window.callsByFloor.options.title.text = "Elevator Calls by Floor";
		
		getData();
	}

function randomSample(max){
	return Math.floor(Math.random() * max);
}
	
function getData(){
		getRequest("php/getData.php", function handle(inputData){
			var values = inputData.split(",");
			
			for(var i =0; i<values.length; i++){
				console.log(values[i]);
			}
			
			//requts per floor
			var ctx = window.FloorCount;
			for(var i =0; i<3; i++){
				if(values[i] != null){
					ctx.data.datasets[0].data[i] = values[i];
				}else{
					ctx.data.datasets[0].data[i] = 0;
				}
			}
			ctx.update();
			
			//last 10 requests
			var ctx2 = window.last10;
			for(var i =0; i<10; i++){
				if(values[6+i] != null){
					ctx2.data.datasets[0].data[i] = values[6+i];
				}else{
					ctx2.data.datasets[0].data[i] = null;
				}
			}
			ctx2.update(); 
			
			//evelators calls by floor
			var ctx3 = window.callsByFloor;
			for(var i = 3; i<6; i++){
				if(values[i] != null){
					ctx3.data.datasets[0].data[i-3] = values[i];
				}else{
					ctx3.data.datasets[0].data[i-3] = 0;
				}
			}
			ctx3.update();
			
			
			//last hour
			var ctx4 = window.lastHour;
			console.log("There were " + values[16] + " requests in the last hour");
			
			for(var i=0; i < ctx4.data.labels.length; i++){
				ctx4.data.labels[i] = "";
				ctx4.data.datasets[0].data[i] = null;
			}
			
			var label = values[16]-1;
			var i = 0;
			while(label >= 0){
				//console.log("floor: " + values[17+i] + " at time: " + values[17+(i+1)]);
				ctx4.data.datasets[0].data[label] = values[17+i];
				ctx4.data.labels[label] = values[17+(i+1)].slice(11, -7);
				label--;
				i+=2;
			}
			//1,1,1,13,0,0,1,2,3,0,0,0,0,0,0,0,15,1,2021-07-26 11:43:00.000000,1,2021-07-26 11:43:00.000000
			ctx4.update();
			
		});
}

function getRequest(request, func){
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			func(this.responseText);
		}
	};
	xhttp.open("GET", request, true);
	xhttp.send();
}
